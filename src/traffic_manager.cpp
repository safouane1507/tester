#include "traffic_manager.h"
#include "vehicle.h"
#include <cmath>
#include <algorithm>
#include "raymath.h" 

// =============================================================================
//  HELPER FUNCTIONS
// =============================================================================

float TrafficManager::GetDistance(const Vector3& a, const Vector3& b) {
    return Vector3Distance(a, b);
}

bool TrafficManager::AreSameDirection(const Vector3& dir1, const Vector3& dir2) {
    float dotProduct = dir1.x * dir2.x + dir1.z * dir2.z;
    return dotProduct > 0.7f;
}

// Check if two vehicles are in the same PHYSICAL lane (ignoring current yielding offset)
// This prevents oscillation (yielding -> thinking you are safe -> moving back -> yielding again)
bool IsInSamePhysicalLane(Vehicle* a, Vehicle* b) {
    Vector3 toB = Vector3Subtract(b->position, a->position);
    Vector3 right = { -a->forward.z, 0, a->forward.x };
    float sideDist = Vector3DotProduct(toB, right);
    // Standard lane width check (approx 2.5m tolerance)
    return fabs(sideDist) < 2.5f;
}

// Standard Collision Check (Respects VISUAL yielding)
// Used to decide if we need to brake or if we can pass
bool TrafficManager::IsInMyLane(Vehicle* me, Vehicle* other) {
    // 1. Calculate effective positions with Lateral Offset
    Vector3 meRight = { -me->forward.z, 0, me->forward.x };
    Vector3 otherRight = { -other->forward.z, 0, other->forward.x };

    Vector3 mePos = Vector3Add(me->position, Vector3Scale(meRight, me->lateralOffset));
    Vector3 otherPos = Vector3Add(other->position, Vector3Scale(otherRight, other->lateralOffset));

    Vector3 toOther = Vector3Subtract(otherPos, mePos);

    float forwardDist = Vector3DotProduct(toOther, me->forward);
    if (forwardDist < 0) return false; // Behind us

    float sideDist = Vector3DotProduct(toOther, meRight);

    // Collision width: 2.2f allows passing if gap is wide enough
    return fabs(sideDist) < 2.2f; 
}

float TrafficManager::Lerp(float start, float end, float amount) {
    return start + amount * (end - start);
}

// =============================================================================
//  SETUP & DRAWING
// =============================================================================

TrafficManager::TrafficManager(float slowDist, float detection)
    : startSlowingDist(slowDist), minSafeDist(4.0f), detectionRange(detection) {}

void TrafficManager::AddController(int id, std::vector<int> nodeIds) {
    TrafficController ctrl;
    
    ctrl.id = id;
    ctrl.nodeIds = nodeIds;
    ctrl.currentState = LIGHT_GREEN; 
    ctrl.timer = 0.0f;
    ctrl.isEmergencyOverride = false; // Initialize new flag
    
    // Default values (will be overwritten by ConfigureTrafficLight)
    ctrl.durationGreen = 15.0f;
    ctrl.durationYellow = 3.0f;
    ctrl.durationRed = 15.0f;
    ctrl.startRedTime = 0.0f;
    ctrl.position = {0,0,0};

    controllers.push_back(ctrl);
}

void TrafficManager::ConfigureTrafficLight(int controllerId, Vector3 position, float rotation, float startRedTime, float greenTime, float yellowTime, float redTime) {
    for (auto& ctrl : controllers) {
        if (ctrl.id == controllerId) {
            ctrl.position = position;
            ctrl.rotation = rotation;
            ctrl.startRedTime = startRedTime;

            // Set Custom Timers
            ctrl.durationGreen = greenTime;
            ctrl.durationYellow = yellowTime;
            ctrl.durationRed = redTime;

            // Logic: Start Red if offset is requested
            if (ctrl.startRedTime > 0.0f) {
                ctrl.currentState = LIGHT_RED;
                ctrl.durationRed = ctrl.startRedTime; 
            }
            break;
        }
    }
}

// =============================================================================
//  DRAWING LOGIC
// =============================================================================
void TrafficManager::DrawTrafficLightModel(Vector3 pos, float angleY, LightState state) {
    rlPushMatrix();
    
    // 1. Move to position
    rlTranslatef(pos.x, pos.y, pos.z);
    
    // 2. Rotate to face the road
    rlRotatef(angleY, 0, 1, 0);

    // --- DRAWING IN LOCAL COORDINATES ---
    
    float poleHeight = 6.0f;
    float armLength = 6.5f; 

    // A. The Pole
    // Note: Chaimae offsets the pole slightly (x=1.0) so the light hangs over 0.0
    DrawCylinder({1.0f, 0.0f, 0.0f}, 0.3f, 0.3f, poleHeight, 16, DARKGRAY);

    // B. The Horizontal Arm
    Vector3 armStart = {1.0f, poleHeight - 0.5f, 0.0f};
    Vector3 armEnd   = {1.0f - armLength, poleHeight - 0.5f, 0.0f};
    DrawCylinderEx(armStart, armEnd, 0.2f, 0.2f, 8, DARKGRAY);

    // C. The Light Box
    Vector3 boxPos = armEnd;
    float w=0.6f, h=1.8f, d=0.6f;
    Vector3 boxCenter = {boxPos.x, boxPos.y - 0.8f, boxPos.z};
    
    DrawCube(boxCenter, w, h, d, BLACK);
    DrawCubeWires(boxCenter, w, h, d, DARKGRAY); 

    // D. The Lights (Red/Yellow/Green)
    float zFace = boxCenter.z + (d/2) + 0.05f; 

    // Colors: Dim if off, Bright if on
    Color cRed    = (state == LIGHT_RED)    ? RED    : (Color){50, 0, 0, 255};   
    Color cYellow = (state == LIGHT_YELLOW) ? ORANGE : (Color){50, 40, 0, 255};
    Color cGreen  = (state == LIGHT_GREEN)  ? GREEN  : (Color){0, 50, 0, 255}; 

    DrawSphere({boxCenter.x, boxCenter.y + 0.5f, zFace}, 0.22f, cRed);    // Top
    DrawSphere({boxCenter.x, boxCenter.y,        zFace}, 0.22f, cYellow); // Middle
    DrawSphere({boxCenter.x, boxCenter.y - 0.5f, zFace}, 0.22f, cGreen);  // Bottom
    
    rlPopMatrix();
}

void TrafficManager::Draw() {
    for (const auto& ctrl : controllers) {
        DrawTrafficLightModel(ctrl.position, ctrl.rotation, ctrl.currentState);
    }
}

// =============================================================================
//  UPDATE LIGHTS
// =============================================================================
void TrafficManager::UpdateLights(float dt, RoadGraph& map, const std::vector<std::unique_ptr<Vehicle>>& vehicles) {
    
    // 1. Reset overrides first (assume normal operation)
    for (auto& ctrl : controllers) ctrl.isEmergencyOverride = false;

    // 2. Check for active emergency vehicles
    Vehicle* emergencyVehicle = nullptr;
    for(const auto& v : vehicles) {
        if(v->IsEmergency() && !v->finished) {
            emergencyVehicle = v.get();
            break; // Found one, prioritize it
        }
    }

    // 3. Logic loop
    for (auto& ctrl : controllers) {
        
        // --- A. Emergency Logic ---
        if (emergencyVehicle != nullptr) {
            // Check if controller is relevant (within 60m of emergency vehicle)
            if (GetDistance(ctrl.position, emergencyVehicle->position) < 120.0f) {
                
                // Determine Axis (X or Z)
                bool isZAxis = fabs(emergencyVehicle->forward.z) > fabs(emergencyVehicle->forward.x);
                
                // Is this controller managing Z roads?
                bool ctrlIsZ = (fabs(ctrl.position.z) > 20.0f); // 34.0f vs 10.5f check

                // Only override if this light controls the ambulance's path
                if (isZAxis == ctrlIsZ) {
                     ctrl.isEmergencyOverride = true; 
                     ctrl.currentState = LIGHT_GREEN; // FORCE GREEN
                } 
                else {
                    // Force RED for cross traffic
                    ctrl.isEmergencyOverride = true; 
                    ctrl.currentState = LIGHT_RED; 
                }
            }
        }

        // --- B. Standard Timer Logic (Only if not overridden) ---
        if (!ctrl.isEmergencyOverride) {
            ctrl.timer += dt;

            switch (ctrl.currentState) {
                case LIGHT_GREEN:
                    if (ctrl.timer >= ctrl.durationGreen) {
                        ctrl.currentState = LIGHT_YELLOW;
                        ctrl.timer = 0.0f;
                    }
                    break;
                case LIGHT_YELLOW:
                    if (ctrl.timer >= ctrl.durationYellow) {
                        ctrl.currentState = LIGHT_RED;
                        ctrl.timer = 0.0f;
                        ctrl.durationRed = 15.0f; 
                    }
                    break;
                case LIGHT_RED:
                    if (ctrl.timer >= ctrl.durationRed) {
                        ctrl.currentState = LIGHT_GREEN;
                        ctrl.timer = 0.0f;
                        ctrl.durationGreen = 15.0f; 
                    }
                    break;
                default: break;
            }
        }

        // --- C. Apply State to Nodes ---
        for (int nodeId : ctrl.nodeIds) {
            try {
                Node& node = map.GetNode(nodeId);
                node.lightState = ctrl.currentState;
            } catch (...) {}
        }
    }
}

// =============================================================================
//  UPDATE VEHICLES  and YIELDING Logic
// =============================================================================

void TrafficManager::UpdateVehicles(std::vector<std::unique_ptr<Vehicle>>& vehicles, const RoadGraph& map) {
    float dt = GetFrameTime();

    // 1. Identify active emergency vehicles
    std::vector<Vehicle*> emergencyVehicles;
    for(const auto& v : vehicles) {
        if(v->IsEmergency() && !v->finished) {
            emergencyVehicles.push_back(v.get());
        }
    }    
    
    for (size_t i = 0; i < vehicles.size(); i++) {
        Vehicle* current = vehicles[i].get();
        if (current->finished) continue;

        //=======EMERGENCY.-.YIELD.-.LOGIC._.
        float targetLateralOffset = 0.0f;
        // --- 1. NON-EMERGENCY VEHICLES: YIELD RIGHT ---
        if (!current->IsEmergency()) {
            for (Vehicle* ev : emergencyVehicles) {
                // Check if EV is behind us AND in the same PHYSICAL lane (ignoring yield offset)
                if (AreSameDirection(current->forward, ev->forward) && 
                    GetDistance(current->position, ev->position) < 80.0f) 
                {
                    Vector3 toMe = Vector3Subtract(current->position, ev->position);
                    if (Vector3DotProduct(ev->forward, toMe) > 0) { // We are ahead
                        if (IsInSamePhysicalLane(ev, current)) {
                             // Yield heavily to the RIGHT (3.5 units)
                             targetLateralOffset = 3.5f;
                        }
                    }
                }
            }
        }
        // --- 2. EMERGENCY VEHICLES: YIELD LEFT (IF BLOCKED) ---
        else {
            // Check if there is a car directly ahead of us that hasn't fully cleared yet
            bool isBlockedAhead = false;
            for (const auto& other : vehicles) {
                if (other.get() == current || other->finished) continue;
                
                if (AreSameDirection(current->forward, other->forward) &&
                    GetDistance(current->position, other->position) < 40.0f) 
                {
                    Vector3 toOther = Vector3Subtract(other->position, current->position);
                    if (Vector3DotProduct(current->forward, toOther) > 0) { // It is ahead
                         // Check if it's blocking our path (using current visual positions)
                         if (IsInMyLane(current, other.get())) {
                             isBlockedAhead = true;
                             break;
                         }
                    }
                }
            }

            if (isBlockedAhead) {
                // If blocked (Road Full/Red Light jam), move LEFT to create a middle lane
                targetLateralOffset = -2.0f;
            } else {
                // If right line is free (Cars moved out of way), pass NORMAL (Center)
                targetLateralOffset = 0.0f;
            }
        }

        // Smoothly apply the offset
        current->lateralOffset = Lerp(current->lateralOffset, targetLateralOffset, 3.0f * dt);
        //===============================================
        if (current->forceMoveTimer > 0.0f) current->forceMoveTimer -= dt;
        
        float targetSpeed = current->desiredSpeed;
        bool emergencyStop = false; 
        bool redLightStop = false;

        // --- 1. TRAFFIC LIGHT LOGIC ---
        for (const auto& ctrl : controllers) {
            bool isManagedNode = false;
            for (int nodeId : ctrl.nodeIds) {
                if (current->targetNodeId == nodeId) {
                    isManagedNode = true;
                    break;
                }
            }

            if (isManagedNode) {
                // If light is RED or YELLOW...
                if (ctrl.currentState == LIGHT_RED || ctrl.currentState == LIGHT_YELLOW) {
                    // ...but allow emergency vehicles to run red lights!
                    if (current->IsEmergency()) {
                        redLightStop = false; 
                    }else{
                        // Standard cars stop
                        Vector3 nodePos = {0,0,0};
                        bool found = false;
                        for(const auto& n : map.GetAllNodes()) {
                            if(n.id == current->targetNodeId) {
                                nodePos = n.pos;
                                found = true;
                                break;
                            }
                        }

                        if (found) {
                            float distToNode = GetDistance(current->position, nodePos); // Uses restored helper

                            if (distToNode < startSlowingDist) {
                                Vector3 toNode = Vector3Subtract(nodePos, current->position);
                                if (Vector3DotProduct(current->forward, toNode) > 0) {
                                    redLightStop = true;
                                }
                            }
                        }
                    } 
                }
            }
        }

        if (redLightStop) emergencyStop = true;
        
        // --- 2. COLLISION LOGIC ---
        float closestGap = 9999.0f;
        Vehicle* closestVehicle = nullptr;
        bool followMode = false;

        float dynamicDetectionRange = detectionRange + (current->speed * 2.0f);
        float dynamicSlowingDist = startSlowingDist + (current->speed * 1.5f);

        for (size_t j = 0; j < vehicles.size(); j++) {
            if (i == j) continue;
            Vehicle* other = vehicles[j].get();
            if (other->finished) continue;

            float dist = GetDistance(current->position, other->position);
            if (dist > dynamicDetectionRange) continue;

            if (AreSameDirection(current->forward, other->forward)) {
                // Use the visual IsInMyLane (respects yielding)
                if (IsInMyLane(current, other)) {
                    float physicalGap = dist - (current->length/2 + other->length/2);
                    if (physicalGap < closestGap && physicalGap > -1.0f) {
                        closestGap = physicalGap;
                        closestVehicle = other;
                        followMode = true;
                    }
                }
            } else {
                // Intersection logic
                if (!current->IsEmergency()) {
                    Vector3 toOther = Vector3Subtract(other->position, current->position);
                    float fwdDist = Vector3DotProduct(toOther, current->forward);
                    float sideDist = Vector3DotProduct(toOther, { -current->forward.z, 0, current->forward.x });
                    if (fwdDist > 0 && fwdDist < (current->length+other->length)/2 + 3.0f && fabs(sideDist) < 2.5f) {
                        emergencyStop = true;
                    }
                }
            }
        }

        // --- ANGRY MODE (NUCLEAR OPTION) ---
        if (current->forceMoveTimer > 0.0f) {
            targetSpeed = 18.0f;     // Force high speed
            current->speed = 18.0f;  // Force physics velocity immediately
            emergencyStop = false;  // Ignore obstacles
            followMode = false;     // Ignore lead car
        }

        else {
            // CALM MODE
            if (emergencyStop) {
                targetSpeed = 0.0f;
            }
            else if (followMode) {
                if (closestGap < minSafeDist) {
                    targetSpeed = 0.0f;
                }
                else if (closestGap < dynamicSlowingDist) {
                    // Using Lerp could be nice here, but keeping your original math for consistency
                    // Or we can use the helper:
                    // float factor = (closestGap - minSafeDist) / (dynamicSlowingDist - minSafeDist);
                    // targetSpeed = Lerp(0.0f, current->desiredSpeed, factor);
                    
                    float factor = (closestGap - minSafeDist) / (dynamicSlowingDist - minSafeDist);
                    if (closestVehicle) {
                        targetSpeed = closestVehicle->speed + (current->desiredSpeed - closestVehicle->speed) * factor;
                    } else {
                        targetSpeed = current->desiredSpeed * factor;
                    }
                }
            }
            // Physics Smoothing
            float acceleration = 10.0f;
            float braking = 15.0f + (current->speed * 0.5f); 

            if (followMode && closestGap < minSafeDist + 2.0f && current->speed > 1.0f) {
                braking = 50.0f; 
            }

            if (current->speed > targetSpeed) {
                current->speed -= braking * dt;
                if (current->speed < targetSpeed) current->speed = targetSpeed;
            } 
            else {
                current->speed += acceleration * dt;
                if (current->speed > targetSpeed) current->speed = targetSpeed;
            }
        }
        
        if (current->speed < 0.0f) current->speed = 0.0f;
    }
}