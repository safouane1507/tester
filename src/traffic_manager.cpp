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

bool TrafficManager::IsInMyLane(Vehicle* me, Vehicle* other) {
    Vector3 toOther = Vector3Subtract(other->position, me->position);

    float forwardDist = Vector3DotProduct(toOther, me->forward);
    if (forwardDist < 0) return false; // Behind us

    Vector3 right = { -me->forward.z, 0, me->forward.x };
    float sideDist = Vector3DotProduct(toOther, right);

    return fabs(sideDist) < 1.8f; // Within lane width
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
void TrafficManager::UpdateLights(float dt, RoadGraph& map) {
    for (auto& ctrl : controllers) {
        ctrl.timer += dt;

        switch (ctrl.currentState) {
            case LIGHT_GREEN:
                if (ctrl.timer >= ctrl.durationGreen) { // Uses custom timer
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

        for (int nodeId : ctrl.nodeIds) {
            try {
                Node& node = map.GetNode(nodeId);
                node.lightState = ctrl.currentState;
            } catch (...) {}
        }
    }
}

// =============================================================================
//  UPDATE VEHICLES
// =============================================================================

void TrafficManager::UpdateVehicles(std::vector<std::unique_ptr<Vehicle>>& vehicles, const RoadGraph& map) {
    float dt = GetFrameTime();
    
    for (size_t i = 0; i < vehicles.size(); i++) {
        Vehicle* current = vehicles[i].get();
        if (current->finished) continue;

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
                if (ctrl.currentState == LIGHT_RED || ctrl.currentState == LIGHT_YELLOW) {
                    
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

            Vector3 toOther = Vector3Subtract(other->position, current->position);
            float fwdDist = Vector3DotProduct(toOther, current->forward);
            float sideDist = Vector3DotProduct(toOther, { -current->forward.z, 0, current->forward.x });
            float combinedHalfLengths = (current->length * 0.5f) + (other->length * 0.5f);

            // A. Check Direction
            if (AreSameDirection(current->forward, other->forward)) { // Uses restored helper
                // B. Check Lane
                if (IsInMyLane(current, other)) { // Uses restored helper
                    float physicalGap = dist - combinedHalfLengths;
                    if (physicalGap < closestGap) {
                        closestGap = physicalGap;
                        closestVehicle = other;
                        followMode = true;
                    }
                }
            } 
            else {
                // Intersection logic
                float safeCrossingDist = combinedHalfLengths + 3.0f + (current->speed * 0.5f);
                if (fwdDist > 0 && fwdDist < safeCrossingDist && fabs(sideDist) < 2.5f) {
                    emergencyStop = true;
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