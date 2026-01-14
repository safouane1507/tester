#ifndef CITY_STRUCTURES_H
#define CITY_STRUCTURES_H

#include "raylib.h"
#include "rlgl.h"
#include <cmath>

// -----------------------------------------------------------------------------
//  Fonctions de Base : Bâtiment générique
// -----------------------------------------------------------------------------
inline void DrawGenericBuilding(Vector3 position, Vector3 size, Color wallColor, Color roofColor , float rotationAngle = 0.0f) 
{
     // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix(); // Sauvegarde la position actuelle du monde
    
    // 1. On déplace le centre du monde sur la position du bâtiment
    rlTranslatef(position.x, position.y, position.z);
    // 2. On tourne (axe Y = 0, 1, 0)
    rlRotatef(rotationAngle, 0, 1, 0); 
    // 3. On "annule" le déplacement pour que les coordonnées ci-dessous restent valides
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------
    // Positions calculées
    Vector3 wallPos = { position.x, position.y + size.y * 0.5f, position.z };
    Vector3 roofPos = { position.x, position.y + size.y + 0.1f, position.z };
    Vector3 roofSize = { size.x * 1.05f, 0.2f, size.z * 1.05f };

    // Murs du bâtiment
    DrawCube(wallPos, size.x, size.y, size.z, wallColor);
    DrawCubeWires(wallPos, size.x, size.y, size.z, DARKGRAY);

    // Toit
    DrawCube(roofPos, roofSize.x, roofSize.y, roofSize.z, roofColor);
    DrawCubeWires(roofPos, roofSize.x, roofSize.y, roofSize.z, GRAY);

    // Fenêtres latérales décoratives
    float winHeight = size.y / 5.0f;
    float winWidth  = size.x / 5.0f;
    float winDepth  = size.z / 5.0f;
    Color windowColor = SKYBLUE;

    for (int side = 0; side < 2; side++) {
        for (int j = 0; j < 3; j++) {

            Vector3 winPos = {
                position.x + size.x * 0.5f + 0.01f,
                position.y + winHeight * (j + 1) + 1.0f,
                position.z + (side == 0 ? 1 : -1) * winDepth
            };

            DrawCube(winPos, 0.1f, winHeight, winWidth, windowColor);
        }
    }
     // --- FIN DE LA ROTATION ---
    rlPopMatrix(); // On remet le monde comme avant pour ne pas affecter les autres bâtiments
}

// ============================================================================
//  STRUCTURES SPÉCIFIQUES
// ============================================================================

// -----------------------------------------------------------------------------
//  Complexe Résidentiel 🏘️
// -----------------------------------------------------------------------------
inline void DrawResidentialComplex(Vector3 position , float rotationAngle = 0.0f)
{
     // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix(); // Sauvegarde la position actuelle du monde
    
    // 1. On déplace le centre du monde sur la position du bâtiment
    rlTranslatef(position.x, position.y, position.z);
    // 2. On tourne (axe Y = 0, 1, 0)
    rlRotatef(rotationAngle, 0, 1, 0); 
    // 3. On "annule" le déplacement pour que les coordonnées ci-dessous restent valides
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------
    DrawGenericBuilding(
        {position.x, 0.0f, position.z},
        {15.0f, 10.0f, 15.0f},
        GRAY, DARKGRAY
    );

    DrawGenericBuilding(
        {position.x + 20.0f, 0.0f, position.z - 10.0f},
        {12.0f, 12.0f, 12.0f},
        RAYWHITE, GRAY
    );

    DrawGenericBuilding(
        {position.x + 10.0f, 0.0f, position.z + 20.0f},
        {10.0f, 20.0f, 10.0f},
        LIGHTGRAY, DARKGRAY
    );
     // --- FIN DE LA ROTATION ---
    rlPopMatrix(); // On remet le monde comme avant pour ne pas affecter les autres bâtiments
}

// -----------------------------------------------------------------------------
//  Maison Détaillée avec Jardin (Detailed House with Yard) 🏡
// -----------------------------------------------------------------------------
inline void DrawDetailedHouse(Vector3 position , float rotationAngle = 0.0f)
{
     // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix(); // Sauvegarde la position actuelle du monde
    
    // 1. On déplace le centre du monde sur la position du bâtiment
    rlTranslatef(position.x, position.y, position.z);
    // 2. On tourne (axe Y = 0, 1, 0)
    rlRotatef(rotationAngle, 0, 1, 0); 
    // 3. On "annule" le déplacement pour que les coordonnées ci-dessous restent valides
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------
    // --- 1. The Yard (Jardin) ---
    float plotSize = 25.0f;
    // Grass base
    DrawCube({position.x, 0.01f, position.z}, plotSize, 0.1f, plotSize, LIME);
    
    // Fence (Clôture) - White borders
    float fenceHeight = 1.5f;
    float fenceThick = 0.3f;
    Color fenceColor = RAYWHITE;
    
    // Back Fence
    DrawCube({position.x, fenceHeight/2, position.z - plotSize/2}, plotSize, fenceHeight, fenceThick, fenceColor);
    // Left Fence
    DrawCube({position.x - plotSize/2, fenceHeight/2, position.z}, fenceThick, fenceHeight, plotSize, fenceColor);
    // Right Fence
    DrawCube({position.x + plotSize/2, fenceHeight/2, position.z}, fenceThick, fenceHeight, plotSize, fenceColor);
    // Front Fence parts (Leaving gap for driveway)
    DrawCube({position.x - 8.0f, fenceHeight/2, position.z + plotSize/2}, 9.0f, fenceHeight, fenceThick, fenceColor);
    DrawCube({position.x + 8.0f, fenceHeight/2, position.z + plotSize/2}, 9.0f, fenceHeight, fenceThick, fenceColor);

    // --- 2. The House Structure ---
    Vector3 housePos = {position.x - 2.0f, 0.0f, position.z - 2.0f};
    
    // Main Body (Living Area)
    DrawCube({housePos.x, 3.5f, housePos.z}, 12.0f, 7.0f, 10.0f, BEIGE);
    DrawCubeWires({housePos.x, 3.5f, housePos.z}, 12.0f, 7.0f, 10.0f, DARKBROWN);

    // Garage (Attached on the right)
    DrawCube({housePos.x + 9.0f, 2.5f, housePos.z + 1.0f}, 7.0f, 5.0f, 8.0f, BEIGE);
    DrawCubeWires({housePos.x + 9.0f, 2.5f, housePos.z + 1.0f}, 7.0f, 5.0f, 8.0f, DARKBROWN);

    // Roofs (Darker color)
    Color roofColor = { 60, 40, 40, 255 }; // Dark Brown
    // Main Roof
    DrawCube({housePos.x, 7.2f, housePos.z}, 13.0f, 0.5f, 11.0f, roofColor);
    // Garage Roof
    DrawCube({housePos.x + 9.0f, 5.2f, housePos.z + 1.0f}, 7.5f, 0.5f, 8.5f, roofColor);

    // Chimney
    DrawCube({housePos.x - 3.0f, 8.0f, housePos.z - 2.0f}, 1.5f, 3.0f, 1.5f, RED);

    // --- 3. Details (Doors & Windows) ---
    
    // Front Door (on Main Body)
    Vector3 doorPos = {housePos.x + 2.0f, 1.5f, housePos.z + 5.01f};
    DrawCube(doorPos, 2.0f, 3.0f, 0.1f, DARKBROWN);
    // Door Knob
    DrawCube({doorPos.x - 0.6f, 1.5f, doorPos.z + 0.1f}, 0.2f, 0.2f, 0.1f, GOLD);

    // Garage Door
    DrawCube({housePos.x + 9.0f, 2.0f, housePos.z + 5.01f}, 5.0f, 4.0f, 0.1f, GRAY);
    // Garage horizontal lines
    for(int i=0; i<4; i++) {
        DrawCube({housePos.x + 9.0f, 1.0f + i*1.0f, housePos.z + 5.05f}, 4.8f, 0.1f, 0.1f, LIGHTGRAY);
    }

    // Windows (SkyBlue with white frames)
    auto DrawWindow = [](Vector3 p, float w, float h) {
        DrawCube(p, w, h, 0.1f, SKYBLUE); // Glass
        DrawCube({p.x, p.y, p.z+0.05f}, w, 0.2f, 0.1f, WHITE); // Horizontal Frame
        DrawCube({p.x, p.y, p.z+0.05f}, 0.2f, h, 0.1f, WHITE); // Vertical Frame
    };

    // Main window left of door
    DrawWindow({housePos.x - 3.0f, 2.5f, housePos.z + 5.01f}, 3.0f, 2.5f);
    // Second floor window
    DrawWindow({housePos.x, 5.5f, housePos.z + 5.01f}, 3.0f, 2.0f);

    // --- 4. Driveway & Walkway ---
    
    // Driveway (Leading to Garage)
    DrawCube({housePos.x + 9.0f, 0.02f, housePos.z + 9.5f}, 5.0f, 0.05f, 9.0f, DARKGRAY);
    
    // Walkway (Leading to Front Door)
    DrawCube({doorPos.x, 0.02f, doorPos.z + 4.0f}, 1.5f, 0.05f, 8.0f, LIGHTGRAY);

    // --- 5. Nature (Tree & Bush) ---
    
    // Tree (Front Left of yard)
    Vector3 treePos = {position.x - 8.0f, 0.0f, position.z + 8.0f};
    DrawCylinder(treePos, 1.0f, 1.0f, 4.0f, 8, BROWN); // Trunk
    DrawSphere({treePos.x, 5.0f, treePos.z}, 3.0f, DARKGREEN); // Leaves

    // Small Bushes (Next to house)
    DrawSphere({housePos.x - 5.0f, 1.0f, housePos.z + 5.5f}, 1.0f, GREEN);
    DrawSphere({housePos.x + 5.0f, 1.0f, housePos.z + 5.5f}, 0.8f, GREEN);
     // --- FIN DE LA ROTATION ---
    rlPopMatrix(); // On remet le monde comme avant pour ne pas affecter les autres bâtiments
}

// -----------------------------------------------------------------------------
//  Clinique Détaillée (3 Niveaux + Parking) 🏥
// -----------------------------------------------------------------------------
inline void DrawDetailedClinic(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix(); // Sauvegarde la position actuelle du monde
    
    // 1. On déplace le centre du monde sur la position du bâtiment
    rlTranslatef(position.x, position.y, position.z);
    // 2. On tourne (axe Y = 0, 1, 0)
    rlRotatef(rotationAngle, 0, 1, 0); 
    // 3. On "annule" le déplacement pour que les coordonnées ci-dessous restent valides
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------


    float floorHeight = 4.0f;
    float width = 18.0f;
    float depth = 14.0f;
    
    Color wallColor = RAYWHITE;       // Clean white medical look
    Color glassColor = { 100, 200, 255, 200 }; // Blue tint for windows
    Color DARKRED = {139,0,0,255};

    // --- 1. Parking Lot (Left Side) ---
    float parkingWidth = 12.0f;
    float parkingDepth = 20.0f;
    Vector3 parkingPos = { position.x - (width/2.0f) - (parkingWidth/2.0f) - 1.0f, 0.02f, position.z };
    
    // Asphalt Base
    DrawCube(parkingPos, parkingWidth, 0.05f, parkingDepth, DARKGRAY);
    DrawCubeWires(parkingPos, parkingWidth, 0.05f, parkingDepth, BLACK);
    
    // Parking Lines (White Strips)
    for (int i = -2; i <= 2; i++) {
        float zOffset = i * 3.5f;
        DrawCube({parkingPos.x, 0.03f, parkingPos.z + zOffset}, parkingWidth * 0.8f, 0.01f, 0.2f, WHITE);
    }
    
    // Parking Entrance Barrier (Simple)
    DrawCube({parkingPos.x, 1.0f, parkingPos.z + parkingDepth/2.0f}, 0.2f, 2.0f, 0.2f, RED); // Post
    DrawCube({parkingPos.x + 2.0f, 1.5f, parkingPos.z + parkingDepth/2.0f}, 4.0f, 0.2f, 0.2f, YELLOW); // Arm

    // --- 2. Level 1: Reception & Entrance (Ground Floor) ---
    Vector3 l1Pos = { position.x, floorHeight/2.0f, position.z };
    
    // Main Block
    DrawCube(l1Pos, width, floorHeight, depth, wallColor);
    DrawCubeWires(l1Pos, width, floorHeight, depth, LIGHTGRAY);
    
    // Large Glass Entrance (Front)
    DrawCube({l1Pos.x, l1Pos.y, l1Pos.z + depth/2.0f + 0.1f}, width * 0.6f, floorHeight - 1.0f, 0.2f, glassColor);
    
    // Blue Canopy over entrance
    DrawCube({l1Pos.x, l1Pos.y + 1.5f, l1Pos.z + depth/2.0f + 1.5f}, width * 0.4f, 0.2f, 3.0f, BLUE);
    // Canopy pillars
    DrawCylinder({l1Pos.x - 3.0f, 1.0f, l1Pos.z + depth/2.0f + 2.8f}, 0.2f, 0.2f, 2.0f, 8, DARKGRAY);
    DrawCylinder({l1Pos.x + 3.0f, 1.0f, l1Pos.z + depth/2.0f + 2.8f}, 0.2f, 0.2f, 2.0f, 8, DARKGRAY);

    // --- 3. Level 2: Examination Rooms ---
    Vector3 l2Pos = { position.x, floorHeight + floorHeight/2.0f, position.z };
    
    // Main Block (Slightly Overhanging)
    DrawCube(l2Pos, width + 1.0f, floorHeight, depth + 1.0f, wallColor);
    DrawCubeWires(l2Pos, width + 1.0f, floorHeight, depth + 1.0f, GRAY);
    
    // Band of Windows
    DrawCube({l2Pos.x, l2Pos.y, l2Pos.z + (depth+1.0f)/2.0f + 0.05f}, width, 1.5f, 0.1f, glassColor); // Front
    DrawCube({l2Pos.x, l2Pos.y, l2Pos.z - (depth+1.0f)/2.0f - 0.05f}, width, 1.5f, 0.1f, glassColor); // Back

    // --- 4. Level 3: Offices & Surgery ---
    Vector3 l3Pos = { position.x, (floorHeight*2.0f) + floorHeight/2.0f, position.z };
    
    // Main Block (Set back slightly for a balcony effect)
    DrawCube(l3Pos, width - 2.0f, floorHeight, depth - 2.0f, wallColor);
    DrawCubeWires(l3Pos, width - 2.0f, floorHeight, depth - 2.0f, GRAY);
    
    // Individual Windows
    float winSize = 1.5f;
    DrawCube({l3Pos.x - 4.0f, l3Pos.y, l3Pos.z + (depth-2.0f)/2.0f + 0.05f}, winSize, winSize, 0.1f, glassColor);
    DrawCube({l3Pos.x + 4.0f, l3Pos.y, l3Pos.z + (depth-2.0f)/2.0f + 0.05f}, winSize, winSize, 0.1f, glassColor);

    // --- 5. Roof & Details ---
    float roofY = (floorHeight * 3.0f);
    
    // Roof Floor
    DrawCube({position.x, roofY, position.z}, width, 0.5f, depth, DARKGRAY);
    
    // HVAC / AC Units on roof
    DrawCube({position.x - 3.0f, roofY + 1.0f, position.z - 2.0f}, 3.0f, 2.0f, 3.0f, LIGHTGRAY);
    DrawCubeWires({position.x - 3.0f, roofY + 1.0f, position.z - 2.0f}, 3.0f, 2.0f, 3.0f, BLACK);
    
    // --- 6. The Medical Sign (Red Cross) ---
    // Mounted on top front of Level 3
    Vector3 signPos = { position.x, roofY + 2.5f, position.z + (depth/2.0f) };
    
    // Vertical Bar
    DrawCube(signPos, 1.0f, 3.0f, 0.5f, RED);
    DrawCubeWires(signPos, 1.0f, 3.0f, 0.5f, DARKRED);
    // Horizontal Bar
    DrawCube(signPos, 3.0f, 1.0f, 0.5f, RED);
    DrawCubeWires(signPos, 3.0f, 1.0f, 0.5f, DARKRED);
    // --- FIN DE LA ROTATION ---
    rlPopMatrix(); // On remet le monde comme avant pour ne pas affecter les autres bâtiments
}

// -----------------------------------------------------------------------------
//  Mosquée Détaillée (Grand Dome & Minarets) 🕌
// -----------------------------------------------------------------------------
inline void DrawDetailedMosque(Vector3 position , float rotationAngle = 0.0f)
{
     // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix(); // Sauvegarde la position actuelle du monde
    
    // 1. On déplace le centre du monde sur la position du bâtiment
    rlTranslatef(position.x, position.y, position.z);
    // 2. On tourne (axe Y = 0, 1, 0)
    rlRotatef(rotationAngle, 0, 1, 0); 
    // 3. On "annule" le déplacement pour que les coordonnées ci-dessous restent valides
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------

    // --- Configuration ---
    float baseWidth = 26.0f;
    float baseDepth = 26.0f;
    float baseHeight = 10.0f;
    
    Color wallColor = RAYWHITE;       // White Marble look
    Color accentColor = { 0, 100, 0, 255 }; // Islamic Green
    Color domeColor = GOLD;
    Color detailColor = BEIGE;

    // --- 1. The Main Prayer Hall (Base) ---
    Vector3 basePos = { position.x, baseHeight / 2.0f, position.z };
    
    // Main Cube
    DrawCube(basePos, baseWidth, baseHeight, baseDepth, wallColor);
    DrawCubeWires(basePos, baseWidth, baseHeight, baseDepth, LIGHTGRAY);
    
    // Decorative Green Band (Top of walls)
    DrawCube({basePos.x, baseHeight - 0.5f, basePos.z}, baseWidth + 0.2f, 1.0f, baseDepth + 0.2f, accentColor);

    // Second Tier (Octagonal/Square transition to dome)
    float tierSize = 18.0f;
    float tierHeight = 4.0f;
    Vector3 tierPos = { position.x, baseHeight + (tierHeight/2.0f), position.z };
    DrawCube(tierPos, tierSize, tierHeight, tierSize, wallColor);
    DrawCubeWires(tierPos, tierSize, tierHeight, tierSize, GRAY);

    // --- 2. The Grand Dome ---
    float domeRadius = 9.0f;
    Vector3 domePos = { position.x, baseHeight + tierHeight, position.z };
    
    // Main Sphere
    DrawSphere(domePos, domeRadius, domeColor);
    
    // Spire (Crescent holder)
    DrawCylinder({domePos.x, domePos.y + domeRadius - 1.0f, domePos.z}, 0.5f, 0.1f, 4.0f, 8, detailColor);
    // The Crescent (Simulated with small spheres/blocks)
    DrawSphere({domePos.x, domePos.y + domeRadius + 3.0f, domePos.z}, 0.6f, GOLD);
    DrawCube({domePos.x, domePos.y + domeRadius + 3.5f, domePos.z}, 0.1f, 0.8f, 0.1f, GOLD);

    // --- 3. The Entrance (Portal / Iwan) ---
    // Protruding section at the front (+Z direction for this example)
    float entranceDepth = 4.0f;
    Vector3 entPos = { position.x, baseHeight/2.0f - 1.0f, position.z + (baseDepth/2.0f) + (entranceDepth/2.0f) };
    
    // Entrance Block
    DrawCube(entPos, 10.0f, baseHeight - 2.0f, entranceDepth, wallColor);
    DrawCubeWires(entPos, 10.0f, baseHeight - 2.0f, entranceDepth, GRAY);
    
    // Arched Doorway (Simulated)
    DrawCube({entPos.x, entPos.y - 1.0f, entPos.z + entranceDepth/2.0f + 0.05f}, 4.0f, 6.0f, 0.1f, DARKGRAY); // Door shadow
    DrawCylinder({entPos.x - 2.0f, entPos.y - 1.0f, entPos.z + entranceDepth/2.0f + 0.1f}, 0.3f, 0.3f, 6.0f, 8, accentColor); // Left Pillar
    DrawCylinder({entPos.x + 2.0f, entPos.y - 1.0f, entPos.z + entranceDepth/2.0f + 0.1f}, 0.3f, 0.3f, 6.0f, 8, accentColor); // Right Pillar
    
    // Stairs
    DrawCube({entPos.x, 0.25f, entPos.z + 3.0f}, 12.0f, 0.5f, 2.0f, LIGHTGRAY);
    DrawCube({entPos.x, 0.75f, entPos.z + 2.0f}, 10.0f, 0.5f, 2.0f, LIGHTGRAY);

    // --- 4. The Minarets (Twin Towers) ---
    // Helper lambda for drawing a detailed minaret
    auto DrawMinaret = [&](float x, float z) {
        float mBaseH = 8.0f;
        float mShaftH = 15.0f;
        float mTopH = 5.0f;
        
        // Base (Square)
        DrawCube({x, mBaseH/2.0f, z}, 3.0f, mBaseH, 3.0f, wallColor);
        
        // Lower Shaft (Cylinder)
        DrawCylinder({x, mBaseH + mShaftH/2.0f, z}, 1.0f, 1.0f, mShaftH, 16, wallColor);
        
        // Balcony (Sherefa) - The ring
        DrawCylinder({x, mBaseH + mShaftH, z}, 1.8f, 1.8f, 0.5f, 16, accentColor);
        
        // Upper Shaft
        DrawCylinder({x, mBaseH + mShaftH + mTopH/2.0f, z}, 0.8f, 0.8f, mTopH, 16, wallColor);
        
        // Roof Cone (Pencil tip)
        DrawCylinder({x, mBaseH + mShaftH + mTopH + 1.5f, z}, 0.0f, 0.9f, 3.0f, 16, domeColor); // Cone using cylinder with top 0
        
        // Finial
        DrawSphere({x, mBaseH + mShaftH + mTopH + 3.0f, z}, 0.4f, GOLD);
    };

    // Place Minarets at front corners
    DrawMinaret(position.x - 12.0f, position.z + 12.0f);
    DrawMinaret(position.x + 12.0f, position.z + 12.0f);

    // --- 5. Windows (Arched Detail) ---
    // Side Windows
    Color winColor = DARKBLUE;
    for(int i = -1; i <= 1; i++) {
        float zOffset = i * 6.0f;
        // Right Side
        DrawCube({position.x + baseWidth/2.0f + 0.05f, 5.0f, position.z + zOffset}, 0.1f, 4.0f, 2.0f, winColor);
        DrawCube({position.x + baseWidth/2.0f + 0.05f, 7.0f, position.z + zOffset}, 0.1f, 0.5f, 2.2f, accentColor); // Arch top hint
        
        // Left Side
        DrawCube({position.x - baseWidth/2.0f - 0.05f, 5.0f, position.z + zOffset}, 0.1f, 4.0f, 2.0f, winColor);
        DrawCube({position.x - baseWidth/2.0f - 0.05f, 7.0f, position.z + zOffset}, 0.1f, 0.5f, 2.2f, accentColor);
    }
     // --- FIN DE LA ROTATION ---
    rlPopMatrix(); // On remet le monde comme avant pour ne pas affecter les autres bâtiments
}

// -----------------------------------------------------------------------------
//  Maison de Ville / Townhouse (Style Brownstone - 2 Unit Block) 🏙️
// -----------------------------------------------------------------------------
inline void DrawDetailedTownhouse(Vector3 position , float rotationAngle = 0.0f)
{
     // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix(); // Sauvegarde la position actuelle du monde
    
    // 1. On déplace le centre du monde sur la position du bâtiment
    rlTranslatef(position.x, position.y, position.z);
    // 2. On tourne (axe Y = 0, 1, 0)
    rlRotatef(rotationAngle, 0, 1, 0); 
    // 3. On "annule" le déplacement pour que les coordonnées ci-dessous restent valides
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------
    // Dimensions for the whole block (2 units)
    float blockWidth = 14.0f;
    float blockHeight = 12.0f; // 3 floors + roof
    float blockDepth = 10.0f;
    
    // Colors
    Color brickColor = { 139, 69, 19, 255 }; // Saddle Brown / Brick
    Color foundationColor = DARKGRAY;
    Color trimColor = BEIGE;
    Color roofColor = { 40, 40, 40, 255 };
    Color windowColor = { 135, 206, 235, 200 }; // Sky Blue

    // --- 1. Main Structure ---
    //Vector3 basePos = { position.x, blockHeight/2.0f, position.z };
    
    // Foundation (Raised basement)
    DrawCube({position.x, 1.0f, position.z}, blockWidth, 2.0f, blockDepth, foundationColor);
    
    // Main Brick Body
    DrawCube({position.x, 1.0f + (blockHeight-2.0f)/2.0f, position.z}, blockWidth, blockHeight - 2.0f, blockDepth, brickColor);
    DrawCubeWires({position.x, 1.0f + (blockHeight-2.0f)/2.0f, position.z}, blockWidth, blockHeight - 2.0f, blockDepth, { 100, 50, 0, 255 });

    // Roof Cornice (Decorative top edge)
    DrawCube({position.x, blockHeight - 0.5f, position.z + blockDepth/2.0f + 0.2f}, blockWidth + 0.5f, 0.8f, 0.5f, trimColor);
    
    // Flat Roof top
    DrawCube({position.x, blockHeight, position.z}, blockWidth - 0.5f, 0.2f, blockDepth - 0.5f, roofColor);

    // --- 2. Unit Details (Loop for Left and Right Unit) ---
    // We offset -3.5 (left unit) and +3.5 (right unit)
    float unitOffset = 3.5f;
    float dirs[2] = { -1.0f, 1.0f };

    for (int i = 0; i < 2; i++) {
        float dir = dirs[i];
        float centerX = position.x + (dir * unitOffset); // Center of this unit
        
        // A. The Stoop (Stairs leading to raised door)
        // Stairs
        for(int s=0; s<5; s++) {
            DrawCube({centerX - 1.5f, 0.2f + s*0.4f, position.z + blockDepth/2.0f + 0.5f + s*0.4f}, 2.0f, 0.4f, 2.5f - s*0.4f, LIGHTGRAY);
        }
        // Railings
        DrawCube({centerX - 2.5f, 1.5f, position.z + blockDepth/2.0f + 1.5f}, 0.1f, 2.0f, 2.5f, BLACK);
        DrawCube({centerX - 0.5f, 1.5f, position.z + blockDepth/2.0f + 1.5f}, 0.1f, 2.0f, 2.5f, BLACK);

        // B. Doorway
        Vector3 doorPos = {centerX - 1.5f, 3.5f, position.z + blockDepth/2.0f + 0.05f};
        DrawCube(doorPos, 1.8f, 3.0f, 0.1f, DARKGRAY); // Door Frame
        DrawCube({doorPos.x, doorPos.y, doorPos.z+0.02f}, 1.5f, 2.8f, 0.1f, { 60, 20, 20, 255 }); // Mahogany Door
        
        // Door overhang/pediment
        DrawCube({doorPos.x, doorPos.y + 1.6f, doorPos.z + 0.3f}, 2.2f, 0.3f, 0.8f, trimColor);

        // C. Windows (3 Floors of windows on the other side of the unit)
        float windowX = centerX + 1.2f; // To the right of the door
        
        // Floor 1 (Next to door - Tall window)
        DrawCube({windowX, 3.5f, position.z + blockDepth/2.0f + 0.05f}, 2.2f, 3.5f, 0.1f, trimColor); // Frame
        DrawCube({windowX, 3.5f, position.z + blockDepth/2.0f + 0.1f}, 1.8f, 3.1f, 0.1f, windowColor); // Glass

        // Floor 2
        DrawCube({centerX, 7.0f, position.z + blockDepth/2.0f + 0.05f}, 5.5f, 2.5f, 0.1f, trimColor); // Wide Frame
        DrawCube({centerX - 1.5f, 7.0f, position.z + blockDepth/2.0f + 0.1f}, 1.8f, 2.1f, 0.1f, windowColor); // Left Win
        DrawCube({centerX + 1.5f, 7.0f, position.z + blockDepth/2.0f + 0.1f}, 1.8f, 2.1f, 0.1f, windowColor); // Right Win

        // Floor 3
        DrawCube({centerX - 1.5f, 10.0f, position.z + blockDepth/2.0f + 0.05f}, 1.8f, 2.0f, 0.1f, windowColor); 
        DrawCubeWires({centerX - 1.5f, 10.0f, position.z + blockDepth/2.0f + 0.05f}, 1.8f, 2.0f, 0.1f, trimColor);
        DrawCube({centerX + 1.5f, 10.0f, position.z + blockDepth/2.0f + 0.05f}, 1.8f, 2.0f, 0.1f, windowColor);
        DrawCubeWires({centerX + 1.5f, 10.0f, position.z + blockDepth/2.0f + 0.05f}, 1.8f, 2.0f, 0.1f, trimColor);

        // D. Planter Box (Front Garden)
        Vector3 plantPos = {windowX, 0.4f, position.z + blockDepth/2.0f + 1.5f};
        DrawCube(plantPos, 2.5f, 0.8f, 2.0f, DARKGRAY); // Box
        DrawCube({plantPos.x, 0.85f, plantPos.z}, 2.1f, 0.1f, 1.6f, DARKGREEN); // Soil/Grass
        // Small bushes
        DrawSphere({plantPos.x - 0.5f, 1.2f, plantPos.z}, 0.6f, GREEN);
        DrawSphere({plantPos.x + 0.5f, 1.2f, plantPos.z}, 0.7f, LIME);
    }
    
    // Common Chimney
    DrawCube({position.x, blockHeight + 1.5f, position.z}, 2.0f, 3.0f, 1.5f, brickColor);
    DrawCubeWires({position.x, blockHeight + 1.5f, position.z}, 2.0f, 3.0f, 1.5f, BLACK);
     // --- FIN DE LA ROTATION ---
    rlPopMatrix(); // On remet le monde comme avant pour ne pas affecter les autres bâtiments
}

// -----------------------------------------------------------------------------
//  Villa de Luxe (Piscine + Trampoline) 🏊‍♂️
// -----------------------------------------------------------------------------
inline void DrawDetailedVilla(Vector3 position , float rotationAngle = 0.0f)
{
     // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix(); // Sauvegarde la position actuelle du monde
    
    // 1. On déplace le centre du monde sur la position du bâtiment
    rlTranslatef(position.x, position.y, position.z);
    // 2. On tourne (axe Y = 0, 1, 0)
    rlRotatef(rotationAngle, 0, 1, 0); 
    // 3. On "annule" le déplacement pour que les coordonnées ci-dessous restent valides
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------
    // --- 1. The Grounds (Terrain) ---
    float plotSize = 30.0f;
    // Lush Green Grass
    DrawCube({position.x, 0.01f, position.z}, plotSize, 0.1f, plotSize, LIME);
    
    // Boundary Hedges (Dark Green walls)
    float hedgeHeight = 2.0f;
    float hedgeThick = 1.0f;
    Color hedgeColor = DARKGREEN;
    
    // Back Hedge
    DrawCube({position.x, hedgeHeight/2.0f, position.z - plotSize/2.0f}, plotSize, hedgeHeight, hedgeThick, hedgeColor);
    // Left Hedge
    DrawCube({position.x - plotSize/2.0f, hedgeHeight/2.0f, position.z}, hedgeThick, hedgeHeight, plotSize, hedgeColor);
    // Right Hedge
    DrawCube({position.x + plotSize/2.0f, hedgeHeight/2.0f, position.z}, hedgeThick, hedgeHeight, plotSize, hedgeColor);

    // --- 2. The Modern Villa Structure ---
    Vector3 housePos = { position.x - 5.0f, 0.0f, position.z - 5.0f };
    Color concreteColor = RAYWHITE;
    Color woodColor = { 101, 67, 33, 255 }; // Dark Wood
    
    // Ground Floor (Large Living Area)
    DrawCube({housePos.x, 2.5f, housePos.z}, 14.0f, 5.0f, 12.0f, concreteColor);
    DrawCubeWires({housePos.x, 2.5f, housePos.z}, 14.0f, 5.0f, 12.0f, LIGHTGRAY);
    
    // Wood Accent Wall / Garage Door
    DrawCube({housePos.x - 4.0f, 2.0f, housePos.z + 6.01f}, 5.0f, 4.0f, 0.1f, woodColor);
    
    // Second Floor (Cantilevered / Overhanging)
    // Shifted slightly to create a modern architectural look
    DrawCube({housePos.x + 1.0f, 6.5f, housePos.z + 1.0f}, 10.0f, 3.0f, 10.0f, concreteColor);
    DrawCubeWires({housePos.x + 1.0f, 6.5f, housePos.z + 1.0f}, 10.0f, 3.0f, 10.0f, LIGHTGRAY);
    
    // Glass Balcony Railing
    DrawCube({housePos.x + 1.0f, 5.5f, housePos.z + 6.0f}, 10.0f, 1.0f, 0.1f, { 200, 200, 255, 150 }); 

    // Large Windows (Cyan tint)
    // Ground floor slider
    DrawCube({housePos.x + 3.0f, 2.5f, housePos.z + 6.01f}, 6.0f, 3.0f, 0.1f, SKYBLUE);
    // Upper floor window
    DrawCube({housePos.x + 1.0f, 7.0f, housePos.z + 6.01f}, 4.0f, 1.5f, 0.1f, SKYBLUE);

    // --- 3. The Swimming Pool Area 💧 ---
    Vector3 poolCenter = { position.x + 8.0f, 0.1f, position.z + 5.0f };
    float poolWidth = 6.0f;
    float poolLength = 10.0f;
    
    // Stone Deck
    DrawCube(poolCenter, poolWidth + 2.0f, 0.2f, poolLength + 2.0f, LIGHTGRAY);
    
    // The Water (Slightly higher than deck bottom, blue and transparent)
    DrawCube({poolCenter.x, 0.25f, poolCenter.z}, poolWidth, 0.1f, poolLength, { 0, 121, 241, 200 });
    
    // Diving Board
    DrawCube({poolCenter.x, 0.5f, poolCenter.z - poolLength/2.0f - 0.5f}, 1.0f, 0.1f, 1.5f, BROWN);
    
    // Sunbeds (Chaises Longues)
    // Simple white wedges
    DrawCube({poolCenter.x - 4.5f, 0.4f, poolCenter.z}, 1.0f, 0.2f, 2.5f, WHITE);
    DrawCube({poolCenter.x - 4.5f, 0.6f, poolCenter.z - 0.8f}, 1.0f, 0.4f, 0.5f, WHITE); // Headrest
    
    DrawCube({poolCenter.x - 4.5f, 0.4f, poolCenter.z + 3.0f}, 1.0f, 0.2f, 2.5f, WHITE);
    DrawCube({poolCenter.x - 4.5f, 0.6f, poolCenter.z + 2.2f}, 1.0f, 0.4f, 0.5f, WHITE); // Headrest

    // --- 4. The Trampoline 🤸 ---
    Vector3 trampPos = { position.x + 8.0f, 0.0f, position.z - 8.0f };
    float trampHeight = 0.8f;
    float trampRadius = 2.5f;
    
    // Legs (4 legs)
    float legOffset = trampRadius * 0.7f;
    Color legColor = DARKGRAY;
    DrawCylinder({trampPos.x + legOffset, trampHeight/2, trampPos.z + legOffset}, 0.05f, 0.05f, trampHeight, 4, legColor);
    DrawCylinder({trampPos.x - legOffset, trampHeight/2, trampPos.z + legOffset}, 0.05f, 0.05f, trampHeight, 4, legColor);
    DrawCylinder({trampPos.x + legOffset, trampHeight/2, trampPos.z - legOffset}, 0.05f, 0.05f, trampHeight, 4, legColor);
    DrawCylinder({trampPos.x - legOffset, trampHeight/2, trampPos.z - legOffset}, 0.05f, 0.05f, trampHeight, 4, legColor);

    // Frame (Blue safety pad)
    DrawCylinder({trampPos.x, trampHeight, trampPos.z}, trampRadius, trampRadius, 0.1f, 16, BLUE);
    
    // Jumping Mat (Black, slightly smaller)
    DrawCylinder({trampPos.x, trampHeight + 0.01f, trampPos.z}, trampRadius - 0.4f, trampRadius - 0.4f, 0.05f, 16, BLACK);
    
    // Safety Net Poles (Optional detail)
    for(int i=0; i<360; i+=90) {
        rlPushMatrix();
        rlTranslatef(trampPos.x, trampHeight, trampPos.z);
        rlRotatef(i + 45, 0, 1, 0);
        DrawCylinder({trampRadius, 1.5f, 0}, 0.05f, 0.05f, 3.0f, 4, GRAY);
        rlPopMatrix();
    }
    // Net (Simulated with faint transparent cylinder walls)
    // Note: Raylib cylinder is solid, so we skip drawing a solid wall to see inside, 
    // or we draw a very transparent gray cylinder.
    DrawCylinderWires({trampPos.x, trampHeight + 1.5f, trampPos.z}, trampRadius, trampRadius, 3.0f, 16, { 200, 200, 200, 50 });
     // --- FIN DE LA ROTATION ---
    rlPopMatrix(); // On remet le monde comme avant pour ne pas affecter les autres bâtiments
}

// -----------------------------------------------------------------------------
//  Grand Magasin / Superstore (Type Walmart/IKEA) 🛒
// -----------------------------------------------------------------------------
inline void DrawBigStore(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------

    // --- DIMENSIONS x1.3 (Retour au format "Massif") ---
    float buildingW = 58.5f; // 45 * 1.3
    float buildingH = 11.7f; // 9 * 1.3
    float buildingD = 39.0f; // 30 * 1.3
    
    // Colors
    Color SILVER = { 192, 192, 192, 255 };
    Color wallColor = RAYWHITE;       
    Color brandColor = { 0, 113, 206, 255 }; 
    Color logoColor = GOLD;           
    Color glassColor = { 200, 230, 255, 120 }; 

    // --- 1. Parking Lot (Très grand) ---
    float parkDepth = 32.5f; // 25 * 1.3
    Vector3 parkPos = { position.x, 0.02f, position.z + buildingD/2.0f + parkDepth/2.0f };
    
    // Asphalt
    DrawCube(parkPos, buildingW + 20.0f, 0.05f, parkDepth, DARKGRAY);
    
    // Parking Lines (Boucle étendue)
    for (float x = -26.0f; x <= 26.0f; x += 4.5f) {
        if (abs(x) < 5.0f) continue; // Skip center lane
        DrawCube({parkPos.x + x, 0.03f, parkPos.z}, 0.25f, 0.01f, parkDepth - 2.0f, WHITE);
    }
    
    // Abris caddies (Écartés)
    DrawCube({parkPos.x - 16.0f, 1.0f, parkPos.z}, 2.6f, 2.5f, 4.0f, LIGHTGRAY);
    DrawCubeWires({parkPos.x - 16.0f, 1.0f, parkPos.z}, 2.6f, 2.5f, 4.0f, brandColor);
    DrawCube({parkPos.x + 16.0f, 1.0f, parkPos.z}, 2.6f, 2.5f, 4.0f, LIGHTGRAY);
    DrawCubeWires({parkPos.x + 16.0f, 1.0f, parkPos.z}, 2.6f, 2.5f, 4.0f, brandColor);

    // --- 2. Main Building Shell ---
    Vector3 bPos = { position.x, buildingH/2.0f, position.z };
    
    // Main Block
    DrawCube(bPos, buildingW, buildingH, buildingD, wallColor);
    DrawCubeWires(bPos, buildingW, buildingH, buildingD, LIGHTGRAY);
    
    // Blue Brand Stripe (Plus épaisse)
    DrawCube({bPos.x, buildingH - 1.3f, bPos.z + buildingD/2.0f + 0.1f}, buildingW, 2.6f, 0.1f, brandColor);

    // --- 3. Entrance ---
    float entranceW = 13.0f;
    float entranceH = 6.0f;
    Vector3 entPos = { position.x, entranceH/2.0f, position.z + buildingD/2.0f + 0.1f };
    
    DrawCube(entPos, entranceW, entranceH, 0.2f, glassColor);
    DrawCubeWires(entPos, entranceW, entranceH, 0.2f, SILVER);
    
    // Logo
    Vector3 signPos = { position.x, buildingH - 1.3f, position.z + buildingD/2.0f + 0.2f };
    DrawCube(signPos, 1.3f, 1.3f, 0.1f, logoColor); 

    // --- 4. Interior Details (Espace immense) ---
    // Caisses
    for(int i=-2; i<=2; i++) {
        DrawCube({position.x + i*4.0f, 0.8f, position.z + buildingD/2.0f - 4.5f}, 1.0f, 1.5f, 2.5f, DARKGRAY);
    }

    // Rayonnages (Boucle massive)
    Color shelfColor = { 220, 220, 220, 255 };
    for (float row = -16.0f; row < 14.0f; row += 6.0f) { // Z loops
        for (float col = -24.0f; col < 24.0f; col += 5.0f) { // X loops
             if (abs(col) < 6.5f) continue; // Allée centrale
             
             Vector3 shelfPos = { position.x + col, 2.5f, position.z + row };
             DrawCube(shelfPos, 1.3f, 5.0f, 4.0f, shelfColor); 
             
             Color prodColor = (int)col % 2 == 0 ? RED : GREEN;
             DrawCube({shelfPos.x, 2.5f, shelfPos.z}, 1.4f, 4.0f, 3.8f, prodColor);
        }
    }

    // --- 5. Garden Center (Extension Droite) ---
    Vector3 gardenPos = { position.x + buildingW/2.0f + 5.0f, 2.5f, position.z + 4.0f };
    float gardenW = 10.0f;
    float gardenD = 20.0f;
    
    DrawCubeWires(gardenPos, gardenW, 5.0f, gardenD, DARKGREEN); 
    DrawCubeWires({gardenPos.x, 5.0f, gardenPos.z}, gardenW, 0.1f, gardenD, BROWN);
    DrawCube({gardenPos.x, 1.0f, gardenPos.z}, 2.5f, 1.5f, 15.0f, BROWN);
    DrawCube({gardenPos.x, 1.8f, gardenPos.z}, 2.3f, 0.4f, 15.0f, GREEN);

    // --- 6. Loading Dock ---
    Vector3 dockPos = { position.x, 2.5f, position.z - buildingD/2.0f - 2.5f };
    DrawCube(dockPos, 10.0f, 4.0f, 5.0f, DARKGRAY); 
    DrawCube({dockPos.x - 2.5f, 3.0f, position.z - buildingD/2.0f - 0.1f}, 4.5f, 5.0f, 0.1f, GRAY);
    DrawCube({dockPos.x + 2.5f, 3.0f, position.z - buildingD/2.0f - 0.1f}, 4.5f, 5.0f, 0.1f, GRAY);

    // --- 7. Roof HVAC ---
    DrawCube({position.x - 13.0f, buildingH, position.z}, 5.0f, 2.5f, 6.5f, LIGHTGRAY);
    DrawCube({position.x + 13.0f, buildingH, position.z - 4.0f}, 5.0f, 2.5f, 6.5f, LIGHTGRAY);

    // --- FIN ROTATION ---
    rlPopMatrix();
}
//  Station Service Complète (Pompes, Boutique, Lavage Auto) ⛽
// -----------------------------------------------------------------------------
inline void DrawDetailedGasStation(Vector3 position , float rotationAngle = 0.0f)
{
     // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix(); // Sauvegarde la position actuelle du monde
    
    // 1. On déplace le centre du monde sur la position du bâtiment
    rlTranslatef(position.x, position.y, position.z);
    // 2. On tourne (axe Y = 0, 1, 0)
    rlRotatef(rotationAngle, 0, 1, 0); 
    // 3. On "annule" le déplacement pour que les coordonnées ci-dessous restent valides
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------
    // --- Colors & Dimensions ---
    Color SILVER = { 192, 192, 192, 255 };
    Color brandColor = { 220, 0, 0, 255 }; // Red Branding
    Color brandAccent = WHITE;
    Color concreteColor = { 180, 180, 180, 255 };
    Color glassColor = { 0, 121, 241, 100 }; // Transparent Blue
    
    // --- 1. The Forecourt (Concrete Base) ---
    float lotW = 40.0f;
    float lotD = 30.0f;
    DrawCube({position.x, 0.02f, position.z}, lotW, 0.1f, lotD, DARKGRAY);
    
    // --- 2. The Canopy (Roof over pumps) ---
    Vector3 canopyPos = { position.x - 6.0f, 6.0f, position.z };
    float canopyW = 20.0f;
    float canopyD = 14.0f;
    
    // Roof Block
    DrawCube(canopyPos, canopyW, 1.0f, canopyD, brandColor);
    DrawCubeWires(canopyPos, canopyW, 1.0f, canopyD, MAROON);
    // White Stripe
    DrawCube({canopyPos.x, canopyPos.y, canopyPos.z + canopyD/2.0f + 0.1f}, canopyW, 0.4f, 0.1f, brandAccent);
    
    // Pillars (Holding the roof)
    float pillarH = 6.0f;
    DrawCylinder({canopyPos.x - 6.0f, pillarH/2.0f, canopyPos.z}, 0.5f, 0.5f, pillarH, 8, concreteColor);
    DrawCylinder({canopyPos.x + 6.0f, pillarH/2.0f, canopyPos.z}, 0.5f, 0.5f, pillarH, 8, concreteColor);

    // --- 3. Pump Islands (Les Pompes) ---
    // We create 2 islands, each with 2 pumps (Total 4 pumps)
    for (int i = 0; i < 2; i++) {
        float zOffset = (i == 0) ? -3.0f : 3.0f;
        Vector3 islandPos = { canopyPos.x, 0.2f, canopyPos.z + zOffset };
        
        // Raised Concrete Island
        DrawCube(islandPos, 14.0f, 0.4f, 2.0f, concreteColor);
        
        // Place 2 Pumps per island
        for (int p = -1; p <= 1; p += 2) {
            Vector3 pumpPos = { islandPos.x + (p * 4.0f), 1.2f, islandPos.z };
            
            // Pump Main Body
            DrawCube(pumpPos, 1.2f, 2.0f, 0.8f, WHITE); 
            // Pump Top (Brand Color)
            DrawCube({pumpPos.x, 2.3f, pumpPos.z}, 1.2f, 0.4f, 0.8f, brandColor);
            // Screen area (Black)
            DrawCube({pumpPos.x, 1.6f, pumpPos.z + 0.41f}, 0.8f, 0.5f, 0.1f, BLACK);
            // Hose (Simulated by a thin dark gray cylinder/box on side)
            DrawCube({pumpPos.x - 0.7f, 1.0f, pumpPos.z}, 0.1f, 1.5f, 0.1f, DARKGRAY);
            
            // Safety bollards (Yellow posts) around the island ends
            if (p == -1) DrawCylinder({islandPos.x - 7.5f, 0.5f, islandPos.z}, 0.2f, 0.2f, 1.0f, 6, YELLOW);
            if (p == 1)  DrawCylinder({islandPos.x + 7.5f, 0.5f, islandPos.z}, 0.2f, 0.2f, 1.0f, 6, YELLOW);
        }
    }

    // --- 4. The Shop (Convenience Store) ---
    // Placed behind the canopy
    Vector3 shopPos = { position.x + 10.0f, 2.5f, position.z }; // Shifted right
    float shopW = 12.0f;
    float shopH = 5.0f;
    float shopD = 20.0f; // Long building oriented along Z
    
    // Rotate building logic (or just build it differently)
    // Let's place it at the back (Z+) instead for better layout
    shopPos = { position.x, 2.5f, position.z + 18.0f };
    shopW = 24.0f; // Wide
    shopD = 8.0f;  // Shallow
    
    // Main Shop Body
    DrawCube(shopPos, shopW, shopH, shopD, WHITE);
    DrawCubeWires(shopPos, shopW, shopH, shopD, LIGHTGRAY);
    
    // Shop Windows & Door (Front Face)
    DrawCube({shopPos.x, 2.0f, shopPos.z - shopD/2.0f - 0.05f}, shopW - 4.0f, 3.0f, 0.1f, glassColor);
    // Door Frame
    DrawCube({shopPos.x, 1.5f, shopPos.z - shopD/2.0f - 0.06f}, 3.0f, 3.0f, 0.1f, SILVER); 
    
    // Shop Signage
    DrawCube({shopPos.x, 4.5f, shopPos.z - shopD/2.0f}, shopW, 1.0f, 0.2f, brandColor);

    // --- 5. The Carwash (Tunnel) ---
    // Placed to the right of the shop
    Vector3 washPos = { position.x + 15.0f, 2.5f, position.z + 5.0f };
    //float washW = 6.0f;
    float washL = 14.0f;
    
    // Tunnel Structure (Open ends)
    // Left Wall
    DrawCube({washPos.x - 2.5f, 2.5f, washPos.z}, 0.5f, 5.0f, washL, concreteColor);
    // Right Wall
    DrawCube({washPos.x + 2.5f, 2.5f, washPos.z}, 0.5f, 5.0f, washL, concreteColor);
    // Roof
    DrawCube({washPos.x, 5.2f, washPos.z}, 6.0f, 0.5f, washL, brandColor);
    
    // Internal Brushes (Green/Blue cylinders)
    DrawCylinder({washPos.x - 1.5f, 2.0f, washPos.z}, 0.8f, 0.8f, 3.5f, 8, LIME); // Vertical brush left
    DrawCylinder({washPos.x + 1.5f, 2.0f, washPos.z}, 0.8f, 0.8f, 3.5f, 8, BLUE); // Vertical brush right
    // Top Horizontal Brush
    rlPushMatrix();
        rlTranslatef(washPos.x, 3.5f, washPos.z - 2.0f);
        rlRotatef(90, 0, 0, 1);
        DrawCylinder({0,0,0}, 0.7f, 0.7f, 4.0f, 8, SKYBLUE);
    rlPopMatrix();

    // Entrance "Carwash" Sign
    DrawCube({washPos.x, 4.0f, washPos.z - washL/2.0f}, 4.0f, 1.0f, 0.2f, YELLOW);

    // --- 6. Tall Road Sign ---
    Vector3 signPostPos = { position.x - 15.0f, 0.0f, position.z - 12.0f };
    // Pole
    DrawCylinder({signPostPos.x, 6.0f, signPostPos.z}, 0.3f, 0.3f, 12.0f, 6, SILVER);
    // Logo Box
    DrawCube({signPostPos.x, 11.0f, signPostPos.z}, 4.0f, 3.0f, 0.5f, brandColor);
    DrawCube({signPostPos.x, 11.0f, signPostPos.z}, 3.0f, 2.0f, 0.6f, WHITE); // Inner white box
     // --- FIN DE LA ROTATION ---
    rlPopMatrix(); // On remet le monde comme avant pour ne pas affecter les autres bâtiments
}

// -----------------------------------------------------------------------------
//  POSTE DE POLICE AVEC GRANDE ENSEIGNE DE TOIT 🚓
// -----------------------------------------------------------------------------
inline void DrawDetailedPoliceStation(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------

    // Dimensions
    float buildingW = 22.0f; float buildingH = 7.0f; float buildingD = 14.0f;
    Color WALL_COLOR = { 200, 200, 200, 255 }; // Gris clair
    Color STRIPE_COLOR = { 0, 50, 150, 255 };  // Bleu Police
    Color WINDOW_COLOR = { 100, 100, 100, 255 };
    Color GARAGE_COLOR = { 80, 80, 80, 255 };

    Vector3 pos = { position.x, buildingH/2.0f, position.z };

    // 1. Corps principal & Bande Bleue
    DrawCube(pos, buildingW, buildingH, buildingD, WALL_COLOR);
    DrawCubeWires(pos, buildingW, buildingH, buildingD, DARKGRAY);
    DrawCube({pos.x, pos.y + 1.0f, pos.z}, buildingW + 0.2f, 1.0f, buildingD + 0.2f, STRIPE_COLOR);

    // 2. Entrée (Porte)
    Vector3 doorPos = { pos.x - 5.0f, 1.5f, pos.z + buildingD/2.0f + 0.1f };
    DrawCube({doorPos.x, 0.5f, doorPos.z + 1.0f}, 4.0f, 1.0f, 2.0f, DARKGRAY); 
    DrawCube(doorPos, 3.0f, 3.0f, 0.2f, SKYBLUE); 
    DrawCubeWires(doorPos, 3.0f, 3.0f, 0.2f, DARKBLUE);

    // 3. Garage
    Vector3 garagePos = { pos.x + 8.0f, 2.5f, pos.z + 1.0f };
    DrawCube(garagePos, 8.0f, 5.0f, 12.0f, WALL_COLOR);
    DrawCubeWires(garagePos, 8.0f, 5.0f, 12.0f, DARKGRAY);
    Vector3 garageDoorPos = { garagePos.x, 2.0f, garagePos.z + 6.0f + 0.1f };
    DrawCube(garageDoorPos, 6.0f, 4.0f, 0.1f, GARAGE_COLOR);
    for(float y=0.5f; y<4.0f; y+=0.5f) DrawCube({garageDoorPos.x, y, garageDoorPos.z}, 6.0f, 0.05f, 0.15f, BLACK);

    // --- 4. GRANDE PLAQUE SUR LE TOIT ---
    // Position : Sur le toit, aligné vers l'avant
    float signH = 3.5f; // Hauteur du panneau
    float signW = 16.0f; // Largeur du panneau
    Vector3 signPos = { pos.x, buildingH + signH/2.0f, pos.z + buildingD/2.0f - 1.5f };

    // Le panneau bleu
    DrawCube(signPos, signW, signH, 0.5f, BLUE);
    DrawCubeWires(signPos, signW, signH, 0.5f, SKYBLUE);

    // TEXTE "POLICE" (En gros cubes blancs)
    Color textColor = RAYWHITE;
    float tZ = signPos.z + 0.26f; // Juste devant le panneau bleu
    float th = 0.25f; // Épaisseur des traits (plus gros)
    float tDepth = 0.1f; // Relief

    // Helper pour dessiner les traits
    auto DrawBigStroke = [&](float xOff, float yOff, float w, float h) {
        DrawCube({signPos.x + xOff, signPos.y + yOff, tZ}, w, h, tDepth, textColor);
    };

    float lh = 2.0f; // Hauteur des lettres (Très grandes)

    // P (x ~ -5.0)
    DrawBigStroke(-5.5f, 0.0f, th, lh);      
    DrawBigStroke(-5.0f, 0.9f, 1.0f, th);    
    DrawBigStroke(-5.0f, 0.0f, 1.0f, th);    
    DrawBigStroke(-4.5f, 0.45f, th, 1.0f);   

    // O (x ~ -2.5)
    DrawBigStroke(-2.5f, 0.0f, th, lh);      
    DrawBigStroke(-1.5f, 0.0f, th, lh);      
    DrawBigStroke(-2.0f, 0.9f, 1.0f, th);    
    DrawBigStroke(-2.0f, -0.9f, 1.0f, th);   

    // L (x ~ 0.0)
    DrawBigStroke(-0.2f, 0.0f, th, lh);      
    DrawBigStroke(0.3f, -0.9f, 1.0f, th);    

    // I (x ~ 2.0)
    DrawBigStroke(2.0f, 0.0f, th, lh);       

    // C (x ~ 4.0)
    DrawBigStroke(3.5f, 0.0f, th, lh);      
    DrawBigStroke(4.0f, 0.9f, 1.0f, th);    
    DrawBigStroke(4.0f, -0.9f, 1.0f, th);   

    // E (x ~ 6.0)
    DrawBigStroke(6.0f, 0.0f, th, lh);       
    DrawBigStroke(6.5f, 0.9f, 1.0f, th);     
    DrawBigStroke(6.5f, 0.0f, 1.0f, th);     
    DrawBigStroke(6.5f, -0.9f, 1.0f, th);    

    // 5. Toit et Gyrophares (derrière le panneau)
    DrawCube({pos.x, buildingH, pos.z}, buildingW, 0.5f, buildingD, DARKGRAY);
    // On recule les gyrophares pour qu'ils soient derrière le panneau
    DrawCube({pos.x - 6.0f, buildingH + 0.5f, pos.z}, 1.0f, 0.8f, 1.0f, RED);   
    DrawCube({pos.x - 4.5f, buildingH + 0.5f, pos.z}, 1.0f, 0.8f, 1.0f, BLUE);  
    // Antenne
    DrawCylinderEx({pos.x+5.0f, buildingH, pos.z-4.0f}, {pos.x+5.0f, buildingH+8.0f, pos.z-4.0f}, 0.1f, 0.02f, 8, DARKGRAY);

    // --- FIN ROTATION ---
    rlPopMatrix();
}
// -----------------------------------------------------------------------------
//  BANQUE (BANK) - Large et Solide avec Colonnes 🏛️💰
// -----------------------------------------------------------------------------
inline void DrawDetailedBank(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------

    // Dimensions (Un peu long/large comme demandé)
    float buildingW = 28.0f; // Largeur importante
    float buildingH = 9.0f;
    float buildingD = 16.0f;

    // Couleurs
    Color STONE_COLOR = { 210, 205, 190, 255 }; // Beige Pierre
    Color PILLAR_COLOR = { 230, 230, 220, 255 }; // Plus clair
    Color GOLD_TEXT = { 218, 165, 32, 255 };    // Or pour le texte
    Color GLASS_COLOR = { 0, 100, 150, 150 };   // Vitres teintées bleu/vert

    Vector3 pos = { position.x, buildingH/2.0f, position.z };

    // 1. Fondation (Socle)
    DrawCube({pos.x, 0.5f, pos.z}, buildingW + 2.0f, 1.0f, buildingD + 2.0f, DARKGRAY);

    // 2. Corps principal du bâtiment (Derrière les colonnes)
    // On le recule un peu pour laisser la place aux colonnes devant
    float mainBodyD = buildingD - 4.0f;
    Vector3 mainBodyPos = { pos.x, buildingH/2.0f + 0.5f, pos.z + 2.0f };
    DrawCube(mainBodyPos, buildingW, buildingH, mainBodyD, STONE_COLOR);
    DrawCubeWires(mainBodyPos, buildingW, buildingH, mainBodyD, GRAY);

    // 3. Les Colonnes (4 piliers devant)
    float colH = buildingH - 2.0f; // Hauteur colonnes
    float colW = 1.5f;
    float colZ = pos.z - buildingD/2.0f + 2.5f; // Position Z (devant le mur)
    
    // On dessine 4 colonnes réparties
    float spread = 7.0f;
    DrawCube({pos.x - spread, colH/2.0f + 1.0f, colZ}, colW, colH, colW, PILLAR_COLOR);
    DrawCube({pos.x - (spread/3.0f), colH/2.0f + 1.0f, colZ}, colW, colH, colW, PILLAR_COLOR);
    DrawCube({pos.x + (spread/3.0f), colH/2.0f + 1.0f, colZ}, colW, colH, colW, PILLAR_COLOR);
    DrawCube({pos.x + spread, colH/2.0f + 1.0f, colZ}, colW, colH, colW, PILLAR_COLOR);

    // 4. Le Toit / Fronton (La barre au-dessus des colonnes)
    Vector3 roofPos = { pos.x, buildingH - 0.5f, pos.z - 0.5f };
    DrawCube(roofPos, buildingW + 1.0f, 2.0f, buildingD + 1.0f, STONE_COLOR);
    DrawCubeWires(roofPos, buildingW + 1.0f, 2.0f, buildingD + 1.0f, DARKGRAY);

    // 5. Portes vitrées (Entre les colonnes du milieu)
    Vector3 doorPos = { pos.x, 2.5f, pos.z - buildingD/2.0f + 4.1f }; // Collé au mur du fond
    DrawCube(doorPos, 5.0f, 4.0f, 0.2f, GLASS_COLOR);
    DrawCubeWires(doorPos, 5.0f, 4.0f, 0.2f, GOLD); // Cadre doré

    // --- 6. TEXTE "BANQUE" (Lettres en cubes dorés) ---
    // Position : Sur le fronton, au-dessus des colonnes
    Vector3 textCenter = { pos.x, buildingH - 0.5f, pos.z - buildingD/2.0f - 1.1f };
    
    // Fonction utilitaire pour dessiner un trait de lettre
    auto DrawStroke = [&](float xOff, float yOff, float w, float h) {
        DrawCube({textCenter.x + xOff, textCenter.y + yOff, textCenter.z}, w, h, 0.1f, GOLD_TEXT);
    };

    float th = 0.15f; // Epaisseur trait
    float lh = 1.0f;  // Hauteur lettre

    // B (x ~ -3.5)
    DrawStroke(-3.5f, 0.0f, th, lh);      // Vert gauche
    DrawStroke(-3.2f, 0.45f, 0.5f, th);   // Haut
    DrawStroke(-3.2f, 0.0f, 0.5f, th);    // Milieu
    DrawStroke(-3.2f, -0.45f, 0.5f, th);  // Bas
    DrawStroke(-2.9f, 0.25f, th, 0.4f);   // Vert droite haut
    DrawStroke(-2.9f, -0.25f, th, 0.4f);  // Vert droite bas

    // A (x ~ -2.0)
    DrawStroke(-2.2f, -0.1f, th, lh*0.8f); // Jambe gauche
    DrawStroke(-1.8f, -0.1f, th, lh*0.8f); // Jambe droite
    DrawStroke(-2.0f, 0.45f, 0.5f, th);    // Top chapeau
    DrawStroke(-2.0f, 0.0f, 0.5f, th);     // Barre milieu

    // N (x ~ -0.5)
    DrawStroke(-0.8f, 0.0f, th, lh);      // Gauche
    DrawStroke(-0.2f, 0.0f, th, lh);      // Droite
    // Diagonale simulée par 2 petits blocs
    DrawStroke(-0.6f, 0.2f, th, 0.3f);
    DrawStroke(-0.4f, -0.2f, th, 0.3f);

    // Q (x ~ 1.0)
    DrawStroke(0.7f, 0.0f, th, lh);       // Gauche
    DrawStroke(1.3f, 0.0f, th, lh);       // Droite
    DrawStroke(1.0f, 0.45f, 0.6f, th);    // Haut
    DrawStroke(1.0f, -0.45f, 0.6f, th);   // Bas
    DrawStroke(1.2f, -0.5f, th, 0.4f);    // Queue du Q

    // U (x ~ 2.5)
    DrawStroke(2.2f, 0.1f, th, lh*0.9f);  // Gauche
    DrawStroke(2.8f, 0.1f, th, lh*0.9f);  // Droite
    DrawStroke(2.5f, -0.45f, 0.6f, th);   // Bas

    // E (x ~ 4.0)
    DrawStroke(3.7f, 0.0f, th, lh);       // Gauche
    DrawStroke(4.0f, 0.45f, 0.6f, th);    // Haut
    DrawStroke(3.9f, 0.0f, 0.5f, th);     // Milieu
    DrawStroke(4.0f, -0.45f, 0.6f, th);   // Bas
    // ------------------------------------------

    // 7. Distributeur de billets (ATM) - Sur le côté droit
    Vector3 atmPos = { pos.x + buildingW/2.0f - 2.0f, 1.5f, pos.z + buildingD/2.0f + 0.1f }; // Sur le mur arrière ou côté
    // Mettons-le sur le mur avant, à droite des colonnes
    atmPos = { pos.x + 8.0f, 1.5f, colZ }; 
    
    DrawCube(atmPos, 1.5f, 2.5f, 0.5f, DARKGRAY); // La machine
    DrawCube({atmPos.x, atmPos.y + 0.5f, atmPos.z + 0.3f}, 1.0f, 0.8f, 0.1f, GREEN); // Ecran
    DrawCube({atmPos.x, atmPos.y - 0.2f, atmPos.z + 0.3f}, 1.0f, 0.1f, 0.2f, BLACK); // Fente billets

    // --- FIN ROTATION ---
    rlPopMatrix();
}
#endif