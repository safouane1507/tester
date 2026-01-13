#include "camera_controller.h"
#include "raymath.h"
#include <cmath> // Needed for sin, cos, atan2, asin

namespace CameraController {

    void Init(Camera3D& camera) {
        camera.projection = CAMERA_PERSPECTIVE;
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Always keep Y as UP
    }

    void Update(Camera3D& camera, const CameraConfig& config) {
        float dt = GetFrameTime();

        // --- 1. DECONSTRUCT: Calculate Current Spherical Coordinates ---
        // Vector from Target (center) to Camera
        Vector3 camDiff = Vector3Subtract(camera.position, camera.target);
        
        // DISTANCE (Radius)
        float distance = Vector3Length(camDiff);
        
        // YAW (Horizontal Angle: 0 to 360)
        // atan2 gives us the angle on the X/Z plane
        float yaw = atan2f(camDiff.x, camDiff.z);
        
        // PITCH (Vertical Angle: 0 to 90)
        // We calculate angle relative to the ground plane
        // Clamp prevents math errors if y > distance (floating point error)
        float pitch = asinf(Clamp(camDiff.y / distance, -1.0f, 1.0f));

        // --- 2. INPUT: ZOOM (Distance) ---
        float zoomInput = GetMouseWheelMove();
        // Support Arrow Keys for Zoom too
        if (IsKeyDown(KEY_UP)) zoomInput += 1.0f * dt * 5.0f;
        if (IsKeyDown(KEY_DOWN)) zoomInput -= 1.0f * dt * 5.0f;

        if (zoomInput != 0.0f) {
            distance -= zoomInput * config.zoomSpeed;
            // Clamp Zoom
            if (distance < config.minDistance) distance = config.minDistance;
            if (distance > config.maxDistance) distance = config.maxDistance;
        }

        // --- 3. INPUT: ROTATION (Yaw & Pitch) ---
        // Mouse Right Click Drag OR WASD
        
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // Mouse Control (Drag to spin)
            Vector2 delta = GetMouseDelta();
            yaw   -= delta.x * 0.005f; // Turn Horizontal
            pitch += delta.y * 0.005f; // Turn Vertical
        } else {
            // WASD Control
            if (IsKeyDown(KEY_A)) yaw   -= config.orbitSpeed * dt; // Spin Left
            if (IsKeyDown(KEY_D)) yaw   += config.orbitSpeed * dt; // Spin Right
            if (IsKeyDown(KEY_W)) pitch += config.orbitSpeed * dt; // Look Higher
            if (IsKeyDown(KEY_S)) pitch -= config.orbitSpeed * dt; // Look Lower
        }

        // --- 4. APPLY "HALF SPHERE" LIMITS ---
        // This ensures we NEVER go underground (minPitch)
        // And never flip over the top (maxPitch)
        if (pitch < config.minPitch) pitch = config.minPitch;
        if (pitch > config.maxPitch) pitch = config.maxPitch;

        // --- 5. RECONSTRUCT POSITION ---
        // Convert Spherical (Yaw, Pitch, Distance) back to Cartesian (X, Y, Z)
        
        // Y is determined by the pitch angle (Height)
        camDiff.y = distance * sinf(pitch);
        
        // Horizontal distance on the ground
        float hDist = distance * cosf(pitch);
        
        // X and Z are determined by the yaw angle
        camDiff.x = hDist * sinf(yaw);
        camDiff.z = hDist * cosf(yaw);

        // Apply new position relative to target
        camera.position = Vector3Add(camera.target, camDiff);

        // --- 6. PANNING (Moving the Target Center) ---
        // Use Middle Mouse Button to drag the map center
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
            Vector2 delta = GetMouseDelta();
            
            // Calculate Forward and Right vectors flat on the ground
            // This ensures panning feels correct regardless of rotation
            Vector3 forward = (Vector3){ sinf(yaw), 0, cosf(yaw) };
            Vector3 right   = (Vector3){ cosf(yaw), 0, -sinf(yaw) };

            Vector3 move = Vector3Zero();
            move = Vector3Add(move, Vector3Scale(right, -delta.x * config.panSpeed));
            move = Vector3Add(move, Vector3Scale(forward, -delta.y * config.panSpeed));

            // Move BOTH target and position
            camera.target = Vector3Add(camera.target, move);
            camera.position = Vector3Add(camera.position, move);
        }
    }
}