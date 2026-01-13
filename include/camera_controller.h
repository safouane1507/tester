#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "raylib.h"

struct CameraConfig {
    // Speeds
    float orbitSpeed = 2.0f;   // Speed of rotation (WASD)
    float zoomSpeed = 10.0f;   // Speed of zooming (Wheel)
    float panSpeed = 0.5f;     // Speed of moving the map (Middle Click)

    // Limits
    float minDistance = 20.0f; // Closest zoom
    float maxDistance = 400.0f;// Furthest zoom
    
    // The "Half Sphere" Limits (In Radians)
    // 0.05 rad = very close to ground (but NOT under)
    // 1.50 rad = almost 90 degrees (Top down view)
    float minPitch = 0.05f; 
    float maxPitch = 1.50f; 
};

namespace CameraController {
    // Call once in App constructor
    void Init(Camera3D& camera);

    // Call every frame in App::Update
    void Update(Camera3D& camera, const CameraConfig& config);
}

#endif