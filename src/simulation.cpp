#include "simulation.h"
#include "basicmap.h"
#include "config.h" //.-.
#include <cmath> // Needed for fabs

Simulation::Simulation() : trafficMgr(20.0f, 50.0f) {} 

void Simulation::Init() {
    InitializeRoadNetwork(roadGraph);

    // 1. SOUTH LIGHT (Node 16)
    // Controls traffic entering the roundabout from the South
    trafficMgr.AddController(16, { 16, 17 }); 
    trafficMgr.ConfigureTrafficLight(
        16,                         // ID
        { 10.5f, 0.0f, 34.0f },     // Position (from Chaimae's basicmap.cpp)
        0.0f,                       // Rotation (Face Z+)
        20.0f,                       // Start Delay 20s= red35s -> green50s -> yellow53s
        15.0f, 3.0f, 15.0f          // Timings: Green, Yellow, Red
    );

    // 2. NORTH LIGHT (Node 12)
    // Controls traffic entering from the North
    trafficMgr.AddController(12, { 12, 13 });
    trafficMgr.ConfigureTrafficLight(
        12,                         // ID
        { -10.5f, 0.0f, -34.0f },   // Position
        180.0f,                     // Rotation (Face Z-)
        25.0f,                       // Start Delay 25s= red40s -> green55s -> yellow58s
        15.0f, 3.0f, 15.0f          // Timings: Green, Yellow, Red
    );

    // 3. EAST LIGHT (Node 8)
    // Controls traffic entering from the East
    trafficMgr.AddController(8, { 8, 9 });
    trafficMgr.ConfigureTrafficLight(
        8,                          // ID
        { 34.0f, 0.0f, -10.5f },    // Position
        90.0f,                      // Rotation (Face X+)
        5.0f,                       // Start Delay 5s= red20s -> green35s -> yellow38s
        15.0f, 3.0f, 15.0f          // Timings: Green, Yellow, Red
    );

    // 4. WEST LIGHT (Node 2)
    // Controls traffic entering from the West
    trafficMgr.AddController(2, { 2, 3 });
    trafficMgr.ConfigureTrafficLight(
        2,                          // ID
        { -34.0f, 0.0f, 10.5f },    // Position
        270.0f,                     // Rotation (Face X-)
        0.0f,                       // Start Delay 0= red15s -> green30s -> yellow33s
        15.0f, 3.0f, 15.0f          // Timings: Green, Yellow, Red
    );
}

void Simulation::ApplyConfiguration() {
    vehicles.clear();
    roadGraph.Clear();
    InitializeRoadNetwork(roadGraph);
    spawner.LoadFromConfig();
}

void Simulation::Clear() {
    vehicles.clear();
    spawner.Clear();
}

int Simulation::GetVehicleCount() const {
    return (int)vehicles.size();
}

void Simulation::Update(float dt, Camera3D camera) {
    // 1. Spawner
    spawner.Update(roadGraph, vehicles);

    // =========================================================
    //  INTERACTION
    // =========================================================
    Vector2 mouse = GetMousePosition();
    Vector2 scaledMouse = mouse;
    scaledMouse.x = mouse.x * ((float)SimulationConfig::SCREEN_WIDTH / GetScreenWidth());
    scaledMouse.y = mouse.y * ((float)SimulationConfig::SCREEN_HEIGHT / GetScreenHeight());
    
    Ray ray = GetMouseRay(scaledMouse, camera);
    
    Vehicle* hoveredVehicle = nullptr;
    float minHitDist = 9999.0f; // Track closest hit

    for (auto& v : vehicles) {
        // --- ADAPTIVE HITBOX MATH ---
        // We calculate how much space the car takes on X and Z axes based on its rotation.
        // Width is approx 2.5m for all cars. Length varies.
        float width = 2.5f;
        
        // Project length and width onto the axes
        // If facing X: SizeX = Length, SizeZ = Width
        // If facing Z: SizeX = Width,  SizeZ = Length
        // If 45 deg:   SizeX = Mix,    SizeZ = Mix
        float halfSizeX = (fabs(v->forward.x) * v->length + fabs(v->forward.z) * width) / 2.0f;
        float halfSizeZ = (fabs(v->forward.z) * v->length + fabs(v->forward.x) * width) / 2.0f;

        // Construct the rotating box
        BoundingBox box = {
            (Vector3){ v->position.x - halfSizeX, v->position.y, v->position.z - halfSizeZ },
            (Vector3){ v->position.x + halfSizeX, v->position.y + 2.5f, v->position.z + halfSizeZ }
        };

        // Check Raycast
        RayCollision collision = GetRayCollisionBox(ray, box);
        
        if (collision.hit) {
            // Only pick this car if it is closer than previous hits
            if (collision.distance < minHitDist) {
                minHitDist = collision.distance;
                hoveredVehicle = v.get();
            }
        }
    }
    
    // --- APPLY INTERACTION TO THE WINNER ---
    if (hoveredVehicle != nullptr) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            hoveredVehicle->forceMoveTimer = 2.5f;
        }
    }

    // =========================================================

    // 2. Traffic Logic
    trafficMgr.UpdateLights(dt, roadGraph, vehicles);// Update lights before vehicles
    trafficMgr.UpdateVehicles(vehicles, roadGraph);
    
    // 3. Physics
    for (auto &v : vehicles) {
        v->update(dt, roadGraph, vehicles); 
    }
}

void Simulation::Draw3D(bool showDebugNodes) {
    // 1. Draw the Roads
    DrawBasicMap();

    // 2. Draw the Traffic Lights
    trafficMgr.Draw(); 

    // 3. Draw Debug Nodes
    if (showDebugNodes) roadGraph.DrawNodes();

    // 4. Draw Vehicles
    for (auto &v : vehicles) v->draw();
}

void Simulation::DrawOverlay(bool showDebugNodes, Camera3D camera) {
    if (showDebugNodes) roadGraph.DrawIdNodes(camera);
}