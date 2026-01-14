#ifndef TRAFFIC_MANAGER_H
#define TRAFFIC_MANAGER_H

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <vector>
#include <memory>
#include "roadgraph.h"

// Forward declaration to avoid circular includes
// (We only need to know 'Vehicle' exists here)
class Vehicle; 

// Separated Traffic Controller Struct
struct TrafficController {
    int id;
    std::vector<int> nodeIds;  // List of nodes this controller manages
    Vector3 position;          // Controller position in the world

    float rotation;
    
    // State
    LightState currentState;
    float timer;
    
    // Timings
    float startRedTime;// Delay before starting (or initial Red duration)
    float durationGreen;
    float durationYellow;
    float durationRed;
};

// The TrafficManager handles collision avoidance and speed regulation.
// It acts as the "brain" for the simulation's traffic rules.
class TrafficManager {
private:
    // --- Configuration Parameters ---
    float startSlowingDist;
    float minSafeDist;      
    float detectionRange;   

    std::vector<TrafficController> controllers; 

    // --- Internal Helper Functions ---
    float GetDistance(const Vector3& a, const Vector3& b);  // Calculates Euclidean distance between two 3D points
    bool AreSameDirection(const Vector3& dir1, const Vector3& dir2);  // Direction Check (Are we parallel?)
    bool IsInMyLane(Vehicle* me, Vehicle* other);  // Lane Check (Only for parallel cars)
    float Lerp(float start, float end, float amount);   // Linear Interpolation helper for smooth braking

    // NEW: Specific rendering function for lights
    void DrawTrafficLightModel(Vector3 pos, float angleY, LightState state);

public:
    // Constructor with default safety values
    TrafficManager(float slowDist = 12.0f, float detection = 30.0f);

    // Setup & Config
    void AddController(int id, std::vector<int> nodeIds);
    void ConfigureTrafficLight(int controllerId, Vector3 position, float rotation, float startRedTime, float greenTime, float yellowTime, float redTime);
    
    // Draw Loop
    void Draw();
    
    // Update Loops
    void UpdateLights(float dt, RoadGraph& map); 
    void UpdateVehicles(std::vector<std::unique_ptr<Vehicle>>& vehicles, const RoadGraph& map);
};

#endif // TRAFFIC_MANAGER_H