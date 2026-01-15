#ifndef CITY_STRUCTURES_H
#define CITY_STRUCTURES_H

// -----------------------------------------------------------------------------
//  Includes
// -----------------------------------------------------------------------------
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
//  GRAND HÔPITAL GÉNÉRAL (9 ÉTAGES + HÉLIPORT + PARKING) 🏥🚁🚗
// -----------------------------------------------------------------------------
inline void DrawDetailedClinic(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------

    // --- DIMENSIONS & CONFIGURATION ---
    int numFloors = 9;             
    float floorHeight = 3.5f;      
    float buildingH = numFloors * floorHeight; 
    
    float buildingW = 26.0f;       
    float buildingD = 18.0f;       

    Vector3 pos = position;
    Vector3 centerPos = { pos.x, buildingH / 2.0f, pos.z };

    // Couleurs
    Color WALL_WHITE = { 245, 245, 250, 255 }; 
    Color GLASS_BLUE = { 100, 150, 250, 200 }; 
    Color CROSS_RED = { 230, 0, 0, 255 };      
    Color ROOF_GRAY = { 80, 80, 80, 255 };
    Color HELIPAD_H = { 255, 255, 0, 255 };
    Color ASPHALT = { 50, 50, 50, 255 };

    // ==========================================================
    // 0. LE PARKING (SUR LE CÔTÉ GAUCHE)
    // ==========================================================
    float parkW = 22.0f;
    float parkD = 30.0f;
    // On le place à gauche du bâtiment avec un petit écart
    Vector3 parkPos = { pos.x - buildingW/2.0f - parkW/2.0f - 2.0f, 0.05f, pos.z };

    // Sol Bitume
    DrawCube(parkPos, parkW, 0.1f, parkD, ASPHALT);

    // Lignes de stationnement (Blanches)
    for (float z = -parkD/2 + 2.0f; z < parkD/2 - 2.0f; z += 3.5f) {
        // Rangée Gauche
        DrawCube({parkPos.x - 6.0f, 0.06f, parkPos.z + z}, 7.0f, 0.1f, 0.2f, WHITE);
        // Rangée Droite
        DrawCube({parkPos.x + 6.0f, 0.06f, parkPos.z + z}, 7.0f, 0.1f, 0.2f, WHITE);
    }

    // Cabine de gardien / Barrière (Entrée parking)
    Vector3 boothPos = { parkPos.x + parkW/2.0f - 2.0f, 1.5f, parkPos.z + parkD/2.0f - 1.0f };
    DrawCube(boothPos, 2.0f, 3.0f, 2.0f, LIGHTGRAY); // Cabine
    DrawCube({boothPos.x, 2.0f, boothPos.z}, 2.1f, 1.0f, 2.1f, GLASS_BLUE); // Vitres cabine
    // La barrière rouge et blanche
    DrawCube({boothPos.x - 3.0f, 1.0f, boothPos.z}, 4.0f, 0.2f, 0.2f, RED); 

    // ==========================================================
    // 1. CORPS DU BÂTIMENT (LA TOUR)
    // ==========================================================
    DrawCube(centerPos, buildingW, buildingH, buildingD, WALL_WHITE);
    DrawCubeWires(centerPos, buildingW, buildingH, buildingD, LIGHTGRAY);

    // Colonnes de renfort
    float colSize = 1.5f;
    DrawCube({pos.x - buildingW/2, centerPos.y, pos.z - buildingD/2}, colSize, buildingH, colSize, LIGHTGRAY);
    DrawCube({pos.x + buildingW/2, centerPos.y, pos.z - buildingD/2}, colSize, buildingH, colSize, LIGHTGRAY);
    DrawCube({pos.x - buildingW/2, centerPos.y, pos.z + buildingD/2}, colSize, buildingH, colSize, LIGHTGRAY);
    DrawCube({pos.x + buildingW/2, centerPos.y, pos.z + buildingD/2}, colSize, buildingH, colSize, LIGHTGRAY);

    // ==========================================================
    // 2. FENÊTRES (ÉTAGES 1 à 8)
    // ==========================================================
    for (int etage = 1; etage < numFloors; etage++) {
        float yLvl = (etage * floorHeight) + 1.5f;

        // Fenêtres Avant/Arrière
        for(float x = -buildingW/2 + 3.0f; x < buildingW/2 - 2.0f; x += 3.0f) {
            DrawCube({pos.x + x, yLvl, pos.z + buildingD/2 + 0.1f}, 2.0f, 1.8f, 0.1f, GLASS_BLUE);
            DrawCube({pos.x + x, yLvl, pos.z - buildingD/2 - 0.1f}, 2.0f, 1.8f, 0.1f, GLASS_BLUE);
        }
        // Fenêtres Côtés
        for(float z = -buildingD/2 + 3.0f; z < buildingD/2 - 2.0f; z += 3.0f) {
             DrawCube({pos.x - buildingW/2 - 0.1f, yLvl, pos.z + z}, 0.1f, 1.8f, 2.0f, GLASS_BLUE);
             DrawCube({pos.x + buildingW/2 + 0.1f, yLvl, pos.z + z}, 0.1f, 1.8f, 2.0f, GLASS_BLUE);
        }
    }

    // ==========================================================
    // 3. CROIX ROUGE (FACADE HAUTE)
    // ==========================================================
    float crossY = buildingH - 4.0f;
    float crossSize = 5.0f;
    float thickness = 1.0f;
    Vector3 crossPos = { pos.x, crossY, pos.z + buildingD/2 + 0.2f };
    
    DrawCube(crossPos, thickness, crossSize, 0.5f, CROSS_RED);
    DrawCube(crossPos, crossSize, thickness, 0.5f, CROSS_RED);
    DrawCubeWires(crossPos, crossSize, thickness, 0.5f, WHITE); // Contour blanc

    // ==========================================================
    // 4. TOIT & HÉLIPORT
    // ==========================================================
    DrawCube({pos.x, buildingH, pos.z}, buildingW, 0.5f, buildingD, ROOF_GRAY);
    
    // Base héliport
    DrawCylinderEx({pos.x, buildingH+0.1f, pos.z}, {pos.x, buildingH+0.2f, pos.z}, 6.0f, 6.0f, 16, DARKGRAY);
    DrawCylinderEx({pos.x, buildingH+0.2f, pos.z}, {pos.x, buildingH+0.3f, pos.z}, 5.5f, 5.5f, 16, BLACK);
    
    // Lettre H
    DrawCube({pos.x - 1.5f, buildingH + 0.35f, pos.z}, 0.5f, 0.1f, 4.0f, HELIPAD_H);
    DrawCube({pos.x + 1.5f, buildingH + 0.35f, pos.z}, 0.5f, 0.1f, 4.0f, HELIPAD_H);
    DrawCube({pos.x, buildingH + 0.35f, pos.z}, 3.5f, 0.1f, 0.5f, HELIPAD_H);

    // ==========================================================
    // 5. ENTRÉE URGENCES (REZ-DE-CHAUSSÉE)
    // ==========================================================
    Vector3 entPos = { pos.x, 2.5f, pos.z + buildingD/2 + 2.0f };
    DrawCube(entPos, 8.0f, 0.2f, 4.0f, GLASS_BLUE); // Toit auvent
    DrawCube({entPos.x - 3.5f, 1.25f, entPos.z + 1.8f}, 0.2f, 2.5f, 0.2f, DARKGRAY); // Poteau G
    DrawCube({entPos.x + 3.5f, 1.25f, entPos.z + 1.8f}, 0.2f, 2.5f, 0.2f, DARKGRAY); // Poteau D
    
    // Panneau Rouge "URGENCES"
    DrawCube({pos.x, 3.5f, pos.z + buildingD/2 + 0.2f}, 4.0f, 0.8f, 0.2f, RED);
    DrawCube({pos.x, 3.5f, pos.z + buildingD/2 + 0.3f}, 3.0f, 0.2f, 0.1f, WHITE);

    // --- FIN ROTATION ---
    rlPopMatrix();
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
//  GRAND IMMEUBLE RÉSIDENTIEL (12 ÉTAGES + BALCONS) 🏢🏙️
// -----------------------------------------------------------------------------
inline void DrawDetailedTownhouse(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------

    // --- CONFIGURATION ---
    int numFloors = 12;            // 12 Étages !
    float floorHeight = 3.0f;      // Hauteur par étage
    float buildingH = numFloors * floorHeight;
    
    float buildingW = 14.0f;       // Largeur standard
    float buildingD = 14.0f;       // Profondeur (carré)

    Vector3 pos = position;
    // Centre vertical du bâtiment
    Vector3 centerPos = { pos.x, buildingH / 2.0f, pos.z };

    // Couleurs
    Color WALL_BEIGE = { 230, 220, 210, 255 }; // Beige pierre
    Color BALCONY_COLOR = { 100, 100, 100, 255 }; // Gris béton
    Color GLASS = { 50, 100, 150, 200 };
    Color ROOF_COLOR = { 60, 60, 60, 255 };
    Color ENTRANCE_COLOR = { 40, 40, 40, 255 };

    // ==========================================================
    // 1. STRUCTURE PRINCIPALE (LA TOUR)
    // ==========================================================
    DrawCube(centerPos, buildingW, buildingH, buildingD, WALL_BEIGE);
    DrawCubeWires(centerPos, buildingW, buildingH, buildingD, LIGHTGRAY);

    // ==========================================================
    // 2. BOUCLE DES ÉTAGES (FENÊTRES ET BALCONS)
    // ==========================================================
    // On commence à l'étage 1 (le 0 est le RDC) jusqu'en haut
    for (int i = 1; i < numFloors; i++) {
        float y = (i * floorHeight) + 1.5f;

        // --- FAÇADE AVANT (AVEC BALCONS) ---
        // On place 2 grands balcons par étage ou 3 fenêtres
        for (float x = -4.0f; x <= 4.0f; x += 4.0f) {
            // Porte-fenêtre
            DrawCube({pos.x + x, y, pos.z + buildingD/2 + 0.1f}, 2.0f, 2.0f, 0.1f, GLASS);
            
            // Le Balcon (sort du mur)
            Vector3 balcPos = { pos.x + x, y - 1.0f, pos.z + buildingD/2 + 0.8f };
            DrawCube(balcPos, 2.5f, 0.2f, 1.5f, BALCONY_COLOR); // Sol balcon
            DrawCube({balcPos.x, balcPos.y + 0.5f, balcPos.z + 0.7f}, 2.5f, 1.0f, 0.1f, GLASS); // Rambarde verre
            DrawCubeWires({balcPos.x, balcPos.y + 0.5f, balcPos.z + 0.7f}, 2.5f, 1.0f, 0.1f, DARKGRAY); // Cadre
        }

        // --- FAÇADES ARRIÈRE ET CÔTÉS (FENÊTRES SIMPLES) ---
        // Arrière
        DrawCube({pos.x - 3.0f, y, pos.z - buildingD/2 - 0.1f}, 2.0f, 1.5f, 0.1f, GLASS);
        DrawCube({pos.x + 3.0f, y, pos.z - buildingD/2 - 0.1f}, 2.0f, 1.5f, 0.1f, GLASS);
        
        // Côté Gauche
        DrawCube({pos.x - buildingW/2 - 0.1f, y, pos.z}, 0.1f, 1.5f, 2.0f, GLASS);
        DrawCube({pos.x - buildingW/2 - 0.1f, y, pos.z - 4.0f}, 0.1f, 1.5f, 2.0f, GLASS);
        DrawCube({pos.x - buildingW/2 - 0.1f, y, pos.z + 4.0f}, 0.1f, 1.5f, 2.0f, GLASS);

        // Côté Droit
        DrawCube({pos.x + buildingW/2 + 0.1f, y, pos.z}, 0.1f, 1.5f, 2.0f, GLASS);
        DrawCube({pos.x + buildingW/2 + 0.1f, y, pos.z - 4.0f}, 0.1f, 1.5f, 2.0f, GLASS);
        DrawCube({pos.x + buildingW/2 + 0.1f, y, pos.z + 4.0f}, 0.1f, 1.5f, 2.0f, GLASS);
    }

    // ==========================================================
    // 3. REZ-DE-CHAUSSÉE (HALL D'ENTRÉE)
    // ==========================================================
    // Base plus foncée
    DrawCube({pos.x, 1.5f, pos.z}, buildingW + 0.5f, 3.0f, buildingD + 0.5f, ENTRANCE_COLOR);
    
    // Entrée principale
    Vector3 doorPos = { pos.x, 1.5f, pos.z + buildingD/2 + 0.3f };
    DrawCube(doorPos, 5.0f, 2.5f, 0.2f, LIGHTGRAY); // Cadre porte
    DrawCube(doorPos, 4.0f, 2.5f, 0.3f, GLASS);     // Vitre porte
    
    // Auvent (Toit au dessus de l'entrée)
    DrawCube({doorPos.x, 3.2f, doorPos.z + 1.0f}, 6.0f, 0.2f, 2.5f, DARKGRAY);

    // Trottoir devant l'immeuble
    DrawCube({pos.x, 0.1f, pos.z + buildingD/2 + 2.0f}, buildingW, 0.2f, 4.0f, LIGHTGRAY);

    // ==========================================================
    // 4. TOIT (CAGE D'ASCENSEUR)
    // ==========================================================
    // Toit plat
    DrawCube({pos.x, buildingH, pos.z}, buildingW, 0.5f, buildingD, ROOF_COLOR);
    
    // Local technique (Ascenseur)
    DrawCube({pos.x + 2.0f, buildingH + 1.5f, pos.z - 2.0f}, 4.0f, 3.0f, 4.0f, WALL_BEIGE);
    DrawCube({pos.x + 2.0f, buildingH + 1.5f, pos.z - 2.0f}, 4.1f, 3.0f, 4.1f, LIGHTGRAY); // Bordures
    
    // Petite antenne
    DrawLine3D({pos.x + 2.0f, buildingH + 3.0f, pos.z - 2.0f}, {pos.x + 2.0f, buildingH + 8.0f, pos.z - 2.0f}, BLACK);

    // --- FIN ROTATION ---
    rlPopMatrix();
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
//  GRAND COMMISSARIAT CENTRAL (3 ÉTAGES + PARKING) 🚓🏢
// -----------------------------------------------------------------------------
inline void DrawDetailedPoliceStation(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------

    // Dimensions Agrandies
    float buildingW = 22.0f;
    float buildingH = 18.0f; // Beaucoup plus haut (3 étages environ)
    float buildingD = 14.0f;

    // Couleurs
    Color WALL_COLOR = { 220, 220, 220, 255 }; // Gris très clair
    Color STRIPE_COLOR = { 0, 50, 150, 255 };  // Bleu Police
    Color WINDOW_COLOR = { 50, 50, 70, 255 };  // Vitres foncées
    Color GARAGE_COLOR = { 80, 80, 80, 255 };
    Color ASPHALT = { 50, 50, 50, 255 };

    Vector3 pos = { position.x, buildingH/2.0f, position.z };

    // ==========================================================
    // 1. LE PARKING (Ajouté sur la GAUCHE)
    // ==========================================================
    float parkW = 15.0f;
    float parkD = 20.0f;
    Vector3 parkPos = { position.x - buildingW/2.0f - parkW/2.0f - 1.0f, 0.05f, position.z };
    
    // Sol Parking
    DrawCube(parkPos, parkW, 0.1f, parkD, ASPHALT);
    
    // Lignes de stationnement
    for(float z = -parkD/2 + 2.5f; z < parkD/2; z += 3.0f) {
        DrawCube({parkPos.x - 2.0f, 0.06f, parkPos.z + z}, 6.0f, 0.1f, 0.2f, WHITE);
    }
    // Une petite barrière de sécurité pour le parking
    DrawCube({parkPos.x - parkW/2, 0.5f, parkPos.z}, 0.2f, 1.0f, parkD, DARKGRAY);


    // ==========================================================
    // 2. BÂTIMENT PRINCIPAL (3 ÉTAGES)
    // ==========================================================
    DrawCube(pos, buildingW, buildingH, buildingD, WALL_COLOR);
    DrawCubeWires(pos, buildingW, buildingH, buildingD, GRAY);

    // Bande Bleue (Au niveau du 1er étage)
    DrawCube({pos.x, 5.0f, pos.z}, buildingW + 0.2f, 1.5f, buildingD + 0.2f, STRIPE_COLOR);

    // --- Fenêtres des étages supérieurs ---
    // On dessine deux rangées de fenêtres
    for (float y = 9.0f; y < buildingH; y += 5.0f) {
        // Fenêtres Avant
        DrawCube({pos.x - 5.0f, y, pos.z + buildingD/2.0f + 0.1f}, 3.0f, 2.0f, 0.1f, WINDOW_COLOR);
        DrawCube({pos.x + 5.0f, y, pos.z + buildingD/2.0f + 0.1f}, 3.0f, 2.0f, 0.1f, WINDOW_COLOR);
        // Fenêtres Arrière
        DrawCube({pos.x - 5.0f, y, pos.z - buildingD/2.0f - 0.1f}, 3.0f, 2.0f, 0.1f, WINDOW_COLOR);
        DrawCube({pos.x + 5.0f, y, pos.z - buildingD/2.0f - 0.1f}, 3.0f, 2.0f, 0.1f, WINDOW_COLOR);
    }

    // ==========================================================
    // 3. ENTRÉE (Rez-de-chaussée)
    // ==========================================================
    Vector3 doorPos = { pos.x, 2.0f, pos.z + buildingD/2.0f + 0.1f };
    // Marches larges
    DrawCube({doorPos.x, 0.5f, doorPos.z + 1.5f}, 6.0f, 1.0f, 3.0f, DARKGRAY);
    // Portes vitrées
    DrawCube(doorPos, 4.0f, 4.0f, 0.2f, SKYBLUE);
    DrawCubeWires(doorPos, 4.0f, 4.0f, 0.2f, DARKBLUE);
    // Petit toit au dessus de la porte
    DrawCube({doorPos.x, 4.5f, doorPos.z + 1.0f}, 6.0f, 0.2f, 2.5f, DARKGRAY);


    // ==========================================================
    // 4. GARAGE (Sur la DROITE, inchangé)
    // ==========================================================
    Vector3 garagePos = { position.x + buildingW/2.0f + 4.0f, 2.5f, position.z + 2.0f };
    DrawCube(garagePos, 8.0f, 5.0f, 12.0f, WALL_COLOR);
    DrawCubeWires(garagePos, 8.0f, 5.0f, 12.0f, DARKGRAY);
    
    // Porte garage
    Vector3 gDoor = { garagePos.x, 2.0f, garagePos.z + 6.0f + 0.1f };
    DrawCube(gDoor, 6.0f, 4.0f, 0.1f, GARAGE_COLOR);
    for(float y=0.5f; y<4.0f; y+=0.5f) DrawCube({gDoor.x, y, gDoor.z}, 6.0f, 0.05f, 0.15f, BLACK);


    // ==========================================================
    // 5. LA GRANDE PLAQUE SUR LE TOIT (L'ENSEIGNE)
    // ==========================================================
    // Note : On l'ajuste à la nouvelle hauteur (buildingH)
    float signH = 4.0f; 
    float signW = 16.0f; 
    Vector3 signPos = { pos.x, buildingH + signH/2.0f, pos.z + buildingD/2.0f - 1.5f };

    // Panneau Bleu
    DrawCube(signPos, signW, signH, 0.5f, BLUE);
    DrawCubeWires(signPos, signW, signH, 0.5f, SKYBLUE);

    // --- TEXTE "POLICE" (Cubes Blancs) ---
    Color textColor = RAYWHITE;
    float tZ = signPos.z + 0.3f; // Devant
    float th = 0.25f; // Epaisseur
    float tDepth = 0.1f;

    auto DrawBigStroke = [&](float xOff, float yOff, float w, float h) {
        DrawCube({signPos.x + xOff, signPos.y + yOff, tZ}, w, h, tDepth, textColor);
    };
    float lh = 2.0f; // Hauteur lettres

    // P
    DrawBigStroke(-5.5f, 0.0f, th, lh);      
    DrawBigStroke(-5.0f, 0.9f, 1.0f, th);    
    DrawBigStroke(-5.0f, 0.0f, 1.0f, th);    
    DrawBigStroke(-4.5f, 0.45f, th, 1.0f);   
    // O
    DrawBigStroke(-2.5f, 0.0f, th, lh);      
    DrawBigStroke(-1.5f, 0.0f, th, lh);      
    DrawBigStroke(-2.0f, 0.9f, 1.0f, th);    
    DrawBigStroke(-2.0f, -0.9f, 1.0f, th);   
    // L
    DrawBigStroke(-0.2f, 0.0f, th, lh);      
    DrawBigStroke(0.3f, -0.9f, 1.0f, th);    
    // I
    DrawBigStroke(2.0f, 0.0f, th, lh);       
    // C
    DrawBigStroke(3.5f, 0.0f, th, lh);      
    DrawBigStroke(4.0f, 0.9f, 1.0f, th);    
    DrawBigStroke(4.0f, -0.9f, 1.0f, th);   
    // E
    DrawBigStroke(6.0f, 0.0f, th, lh);       
    DrawBigStroke(6.5f, 0.9f, 1.0f, th);     
    DrawBigStroke(6.5f, 0.0f, 1.0f, th);     
    DrawBigStroke(6.5f, -0.9f, 1.0f, th);    

    // Toit & Accessoires
    DrawCube({pos.x, buildingH, pos.z}, buildingW, 0.5f, buildingD, DARKGRAY); // Toit plat
    // Gyrophares (Sur le toit, derrière panneau)
    DrawCube({pos.x - 6.0f, buildingH + 0.5f, pos.z}, 1.0f, 0.8f, 1.0f, RED);   
    DrawCube({pos.x - 4.5f, buildingH + 0.5f, pos.z}, 1.0f, 0.8f, 1.0f, BLUE);  
    // Grande Antenne
    DrawCylinderEx({pos.x+5.0f, buildingH, pos.z-4.0f}, {pos.x+5.0f, buildingH+10.0f, pos.z-4.0f}, 0.2f, 0.05f, 8, DARKGRAY);

    // --- FIN ROTATION ---
    rlPopMatrix();
}
// -----------------------------------------------------------------------------
//  BANQUE (BANK AL-MAGHRIB) - Version Corrigée et Nette 🏛️💰
// -----------------------------------------------------------------------------
inline void DrawDetailedBank(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT DE LA ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------------

    // Dimensions
    float buildingW = 28.0f; float buildingH = 9.0f; float buildingD = 16.0f;
    Color STONE_COLOR = { 210, 205, 190, 255 }; Color PILLAR_COLOR = { 230, 230, 220, 255 };
    Color GLASS_COLOR = { 0, 100, 150, 150 };   
    Color SIGN_BG = { 70, 30, 90, 255 }; Color GOLD_TEXT = { 218, 165, 32, 255 };

    Vector3 pos = { position.x, buildingH/2.0f, position.z };

    // 1. Bâtiment principal
    DrawCube({pos.x, 0.5f, pos.z}, buildingW + 2.0f, 1.0f, buildingD + 2.0f, DARKGRAY);
    Vector3 mainBodyPos = { pos.x, buildingH/2.0f + 0.5f, pos.z + 2.0f };
    DrawCube(mainBodyPos, buildingW, buildingH, buildingD - 4.0f, STONE_COLOR);
    DrawCubeWires(mainBodyPos, buildingW, buildingH, buildingD - 4.0f, GRAY);

    // Colonnes & Portes
    float colH = buildingH - 2.0f; float colW = 1.5f; float colZ = pos.z - buildingD/2.0f + 2.5f;
    float spread = 7.0f;
    DrawCube({pos.x - spread, colH/2.0f + 1.0f, colZ}, colW, colH, colW, PILLAR_COLOR);
    DrawCube({pos.x - spread/3.0f, colH/2.0f + 1.0f, colZ}, colW, colH, colW, PILLAR_COLOR);
    DrawCube({pos.x + spread/3.0f, colH/2.0f + 1.0f, colZ}, colW, colH, colW, PILLAR_COLOR);
    DrawCube({pos.x + spread, colH/2.0f + 1.0f, colZ}, colW, colH, colW, PILLAR_COLOR);
    Vector3 doorPos = { pos.x, 2.5f, pos.z - buildingD/2.0f + 4.1f };
    DrawCube(doorPos, 5.0f, 4.0f, 0.2f, GLASS_COLOR); DrawCubeWires(doorPos, 5.0f, 4.0f, 0.2f, GOLD);
    Vector3 atmPos = { pos.x + 8.0f, 1.5f, colZ }; 
    DrawCube(atmPos, 1.5f, 2.5f, 0.5f, DARKGRAY);
    DrawCube({atmPos.x, atmPos.y + 0.5f, atmPos.z + 0.3f}, 1.0f, 0.8f, 0.1f, GREEN);

    // --- 2. GRANDE PLAQUE SUR LE TOIT ---
    float signH = 7.0f; float signW = 18.0f;
    Vector3 signPos = { pos.x, buildingH + signH/2.0f, pos.z - buildingD/2.0f + 3.0f };
    DrawCube(signPos, signW, signH, 0.5f, SIGN_BG);
    DrawCubeWires(signPos, signW, signH, 0.5f, GOLD);

    // --- CONTENU DE LA PLAQUE (CORRIGÉ) ---
    // CORRECTION 1 : On éloigne un peu plus le texte (0.30f au lieu de 0.26f)
    float tZ = signPos.z - 0.30f; 
    float tDepth = 0.1f; 
    auto DrawGoldBlock = [&](float x, float y, float w, float h) {
        DrawCube({signPos.x + x, signPos.y + y, tZ}, w, h, tDepth, GOLD_TEXT);
    };

    // A. LE LOGO
    float logoY = 1.8f;
    rlPushMatrix(); rlTranslatef(signPos.x, signPos.y + logoY, tZ);
    rlRotatef(45.0f, 0, 0, 1); DrawCube({0,0,0}, 3.5f, 3.5f, tDepth, GOLD_TEXT); rlPopMatrix();
    DrawGoldBlock(0.0f, logoY + 0.5f, 2.0f, 0.5f); DrawGoldBlock(-0.5f, logoY, 0.5f, 1.5f);
    DrawGoldBlock(0.0f, logoY - 0.5f, 2.0f, 0.5f); DrawGoldBlock(0.8f, logoY, 0.5f, 1.0f);

    // B. TEXTE ARABE (Nettoyé)
    float arY = -0.3f;
    DrawGoldBlock(4.0f, arY+0.5f, 0.3f, 0.3f); DrawGoldBlock(3.5f, arY+0.2f, 1.5f, 0.3f); DrawGoldBlock(2.8f, arY+0.6f, 0.3f, 0.3f);
    DrawGoldBlock(2.2f, arY+0.4f, 0.8f, 0.6f); DrawGoldBlock(1.8f, arY+0.8f, 0.3f, 0.3f);
    DrawGoldBlock(0.5f, arY+0.3f, 0.3f, 1.2f); DrawGoldBlock(-0.2f, arY+0.3f, 0.3f, 1.2f);
    DrawGoldBlock(-1.0f, arY+0.4f, 1.2f, 0.6f); DrawGoldBlock(-2.0f, arY+0.3f, 1.5f, 0.3f); DrawGoldBlock(-2.0f, arY+0.8f, 0.3f, 0.3f);
    DrawGoldBlock(-3.0f, arY+0.2f, 0.3f, 0.8f); DrawGoldBlock(-4.2f, arY+0.3f, 1.2f, 0.3f); DrawGoldBlock(-4.2f, arY-0.3f, 0.3f, 0.3f);

    // C. TEXTE FRANÇAIS (CORRIGÉ ET NETTOYÉ)
    float frY = -2.0f; float th = 0.18f; float lh = 0.8f; // Traits un peu plus épais (0.18f)
    auto DrawLetter = [&](float x, float y, char c) {
        // CORRECTION 2 : Lettres redessinées pour être plus propres et sans chevauchements bizarres
        if(c=='B') { DrawGoldBlock(x,y,th,lh); DrawGoldBlock(x+0.3f,y+0.4f,0.6f,th); DrawGoldBlock(x+0.3f,y,0.6f,th); DrawGoldBlock(x+0.3f,y-0.4f,0.6f,th); DrawGoldBlock(x+0.6f,y+0.2f,th,0.4f); DrawGoldBlock(x+0.6f,y-0.2f,th,0.4f); }
        if(c=='A') { DrawGoldBlock(x-0.25f,y-0.1f,th,lh*0.9f); DrawGoldBlock(x+0.25f,y-0.1f,th,lh*0.9f); DrawGoldBlock(x,y+0.4f,0.5f,th); DrawGoldBlock(x,y,0.5f,th); }
        if(c=='N') { DrawGoldBlock(x-0.3f,y,th,lh); DrawGoldBlock(x+0.3f,y,th,lh); DrawGoldBlock(x,y,th,lh); }
        if(c=='K') { DrawGoldBlock(x-0.3f,y,th,lh); DrawGoldBlock(x+0.1f,y+0.2f,th,0.4f); DrawGoldBlock(x+0.3f,y+0.4f,th,0.3f); DrawGoldBlock(x+0.1f,y-0.2f,th,0.4f); DrawGoldBlock(x+0.3f,y-0.4f,th,0.3f); }
        if(c=='L') { DrawGoldBlock(x-0.2f,y,th,lh); DrawGoldBlock(x+0.2f,y-0.4f,0.8f,th); }
        if(c=='-') { DrawGoldBlock(x,y,0.5f,th); }
        if(c=='M') { DrawGoldBlock(x-0.4f,y,th,lh); DrawGoldBlock(x+0.4f,y,th,lh); DrawGoldBlock(x-0.2f,y+0.3f,th,0.4f); DrawGoldBlock(x+0.2f,y+0.3f,th,0.4f); DrawGoldBlock(x,y+0.1f,th,0.3f); }
        if(c=='G') { DrawGoldBlock(x-0.3f,y,th,lh); DrawGoldBlock(x,y+0.4f,0.6f,th); DrawGoldBlock(x,y-0.4f,0.6f,th); DrawGoldBlock(x+0.3f,y-0.2f,th,0.5f); DrawGoldBlock(x+0.1f,y,0.4f,th); }
        if(c=='H') { DrawGoldBlock(x-0.3f,y,th,lh); DrawGoldBlock(x+0.3f,y,th,lh); DrawGoldBlock(x,y,0.6f,th); }
        if(c=='R') { DrawGoldBlock(x-0.3f,y,th,lh); DrawGoldBlock(x+0.1f,y+0.4f,0.8f,th); DrawGoldBlock(x+0.1f,y,0.8f,th); DrawGoldBlock(x+0.5f,y+0.2f,th,0.4f); DrawGoldBlock(x+0.2f,y-0.2f,th,0.5f); DrawGoldBlock(x+0.4f,y-0.4f,th,0.3f); }
        if(c=='I') { DrawGoldBlock(x,y,th,lh); }
    };
    
    // Dessin du texte (Espacement légèrement ajusté)
    float startX = -7.0f; float sp = 1.0f; 
    DrawLetter(startX, frY, 'B'); DrawLetter(startX+sp, frY, 'A'); DrawLetter(startX+sp*2, frY, 'N'); DrawLetter(startX+sp*3, frY, 'K');
    DrawLetter(startX+sp*4.5f, frY, 'A'); DrawLetter(startX+sp*5.5f, frY, 'L'); DrawLetter(startX+sp*6.3f, frY, '-');
    DrawLetter(startX+sp*7.8f, frY, 'M'); DrawLetter(startX+sp*9.0f, frY, 'A'); DrawLetter(startX+sp*10.0f, frY, 'G'); DrawLetter(startX+sp*11.0f, frY, 'H'); DrawLetter(startX+sp*12.0f, frY, 'R'); DrawLetter(startX+sp*13.0f, frY, 'I'); DrawLetter(startX+sp*13.8f, frY, 'B');

    // --- FIN ROTATION ---
    rlPopMatrix();
}

// -----------------------------------------------------------------------------
//  PARC & JARDIN D'ENFANTS ANIMÉ (LIVELY PLAYGROUND GARDEN) 🌳🌷👶
// -----------------------------------------------------------------------------
inline void DrawPlayground(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------

    float groundSize = 24.0f; // Un peu plus grand pour le jardin
    Vector3 center = position;

    // Couleurs
    Color GRASS_COLOR = { 34, 150, 34, 255 }; Color SAND_COLOR = { 240, 230, 140, 255 };
    Color FENCE_COLOR = { 139, 69, 19, 255 }; Color WOOD_COLOR = { 160, 82, 45, 255 };
    Color TREE_TRUNK = { 101, 67, 33, 255 }; Color TREE_LEAVES = { 20, 100, 20, 255 };

    // === HELPERS (Fonctions internes pour simplifier le dessin) ===

    // Helper pour dessiner un arbre Low Poly
    auto DrawSimpleTree = [&](float xOff, float zOff, float heightScale) {
        Vector3 tPos = { center.x + xOff, 0.0f, center.z + zOff };
        // Tronc
        DrawCylinderEx(tPos, {tPos.x, 3.0f * heightScale, tPos.z}, 0.5f*heightScale, 0.3f*heightScale, 6, TREE_TRUNK);
        // Feuillage (2 sphères superposées)
        DrawSphere({tPos.x, 3.5f * heightScale, tPos.z}, 2.0f * heightScale, TREE_LEAVES);
        DrawSphere({tPos.x, 5.0f * heightScale, tPos.z}, 1.5f * heightScale, LIME); // Sphère du haut plus claire
    };

    // Helper pour dessiner un petit massif de fleurs
    auto DrawFlowerPatch = [&](float xOff, float zOff, Color petalColor) {
        Vector3 fPos = { center.x + xOff, 0.05f, center.z + zOff };
        for(int i=0; i<5; i++) { // 5 petites fleurs par massif
            float ox = sinf(i)*0.5f; float oz = cosf(i)*0.5f;
            DrawLine3D({fPos.x+ox, 0.0f, fPos.z+oz}, {fPos.x+ox, 0.5f, fPos.z+oz}, LIME); // Tige
            DrawSphere({fPos.x+ox, 0.55f, fPos.z+oz}, 0.2f, petalColor); // Pétale
        }
    };

    // Helper pour dessiner un enfant (forme "pion" simple)
    auto DrawChild = [&](Vector3 pos, Color shirtColor, bool sitting = false) {
        float bodyH = sitting ? 0.6f : 1.0f;
        float headY = pos.y + bodyH + 0.2f;
        // Corps (Cône tronqué)
        DrawCylinderEx(pos, {pos.x, pos.y + bodyH, pos.z}, 0.4f, 0.25f, 8, shirtColor);
        // Tête (Sphère)
        DrawSphere({pos.x, headY, pos.z}, 0.3f, BEIGE);
    };
    // ==============================================================


    // 1. LE SOL (Herbe plus grande)
    DrawCube({center.x, 0.05f, center.z}, groundSize, 0.1f, groundSize, GRASS_COLOR);

    // --- AJOUT VÉGÉTATION (JARDIN) ---
    // Arbres aux coins et sur les côtés
    DrawSimpleTree(-groundSize/2 + 2.0f, -groundSize/2 + 2.0f, 1.0f); // Coin fond gauche
    DrawSimpleTree(groundSize/2 - 2.0f, -groundSize/2 + 2.0f, 1.1f);  // Coin fond droite
    DrawSimpleTree(-groundSize/2 + 3.0f, groundSize/2 - 3.0f, 0.9f);  // Près entrée gauche

    // Massifs de fleurs
    DrawFlowerPatch(-groundSize/2 + 5.0f, groundSize/2 - 1.0f, YELLOW); // Près entrée
    DrawFlowerPatch(groundSize/2 - 5.0f, groundSize/2 - 1.0f, RED);     // Près entrée
    DrawFlowerPatch(0.0f, -groundSize/2 + 4.0f, PURPLE);    // Près du banc fond

    // 2. LA CLÔTURE & ENTRÉE
    for(float i = -groundSize/2; i <= groundSize/2; i += 2.5f) {
        if(abs(i) < 3.0f && center.z + groundSize/2 > center.z) continue; // Espace pour l'entrée devant
        DrawCube({center.x + i, 0.5f, center.z - groundSize/2}, 0.2f, 1.0f, 0.2f, FENCE_COLOR);
        DrawCube({center.x + i, 0.5f, center.z + groundSize/2}, 0.2f, 1.0f, 0.2f, FENCE_COLOR);
        DrawCube({center.x - groundSize/2, 0.5f, center.z + i}, 0.2f, 1.0f, 0.2f, FENCE_COLOR);
        DrawCube({center.x + groundSize/2, 0.5f, center.z + i}, 0.2f, 1.0f, 0.2f, FENCE_COLOR);
    }
    Vector3 archPos = { center.x, 0.0f, center.z + groundSize/2 };
    DrawCube({archPos.x - 2.5f, 1.5f, archPos.z}, 0.5f, 3.0f, 0.5f, WOOD_COLOR);
    DrawCube({archPos.x + 2.5f, 1.5f, archPos.z}, 0.5f, 3.0f, 0.5f, WOOD_COLOR);
    DrawCube({archPos.x, 3.0f, archPos.z}, 5.5f, 0.5f, 0.5f, WOOD_COLOR);
    // Petit toit sur l'arche pour faire "jardin"
    DrawCube({archPos.x, 3.5f, archPos.z}, 6.0f, 0.2f, 1.5f, TREE_TRUNK);

    // 3. ÉQUIPEMENTS (Légèrement repositionnés)
    // Balançoires (Gauche)
    Vector3 swingPos = { center.x - 6.0f, 0.0f, center.z - 3.0f };
    DrawCube({swingPos.x - 2.5f, 2.0f, swingPos.z}, 0.3f, 4.0f, 0.3f, WOOD_COLOR);
    DrawCube({swingPos.x + 2.5f, 2.0f, swingPos.z}, 0.3f, 4.0f, 0.3f, WOOD_COLOR);
    DrawCube({swingPos.x, 4.0f, swingPos.z}, 5.5f, 0.3f, 0.3f, WOOD_COLOR);
    DrawCube({swingPos.x - 1.2f, 2.5f, swingPos.z}, 0.05f, 3.0f, 0.05f, LIGHTGRAY);
    DrawCube({swingPos.x - 1.2f, 1.0f, swingPos.z}, 0.8f, 0.1f, 0.6f, BLUE);
    // Siège 2 avec un ENFANT dessus !
    DrawCube({swingPos.x + 1.2f, 2.5f, swingPos.z}, 0.05f, 3.0f, 0.05f, LIGHTGRAY);
    DrawCube({swingPos.x + 1.2f, 1.0f, swingPos.z}, 0.8f, 0.1f, 0.6f, BLUE);
    DrawChild({swingPos.x + 1.2f, 1.1f, swingPos.z}, ORANGE, true); // Enfant assis

    // Toboggan (Droite)
    Vector3 slidePos = { center.x + 6.0f, 0.0f, center.z - 3.0f };
    DrawCube({slidePos.x, 1.5f, slidePos.z}, 1.5f, 3.0f, 1.5f, WOOD_COLOR);
    DrawCube({slidePos.x, 3.0f, slidePos.z}, 1.6f, 0.1f, 1.6f, RED);
    for(float y=0.5f; y<3.0f; y+=0.5f) DrawCube({slidePos.x, y, slidePos.z + 0.8f}, 1.0f, 0.1f, 0.1f, YELLOW);
    rlPushMatrix(); rlTranslatef(slidePos.x, 2.0f, slidePos.z - 2.5f); rlRotatef(-35.0f, 1, 0, 0);
    DrawCube({0,0,0}, 1.0f, 0.1f, 4.5f, RED); rlPopMatrix();
    // ENFANT en haut du toboggan
    DrawChild({slidePos.x, 3.05f, slidePos.z}, SKYBLUE, false);

    // Bac à Sable (Devant Gauche)
    Vector3 sandPos = { center.x - 5.0f, 0.2f, center.z + 5.0f };
    float sandSize = 4.0f;
    DrawCube(sandPos, sandSize, 0.2f, sandSize, SAND_COLOR);
    DrawCube({sandPos.x - sandSize/2, 0.3f, sandPos.z}, 0.2f, 0.4f, sandSize, WOOD_COLOR);
    DrawCube({sandPos.x + sandSize/2, 0.3f, sandPos.z}, 0.2f, 0.4f, sandSize, WOOD_COLOR);
    DrawCube({sandPos.x, 0.3f, sandPos.z - sandSize/2}, sandSize, 0.4f, 0.2f, WOOD_COLOR);
    DrawCube({sandPos.x, 0.3f, sandPos.z + sandSize/2}, sandSize, 0.4f, 0.2f, WOOD_COLOR);
    // ENFANT jouant dans le sable (assis plus bas)
    DrawChild({sandPos.x - 0.5f, 0.2f, sandPos.z + 0.5f}, YELLOW, true);

    // Tourniquet (Devant Droite)
    Vector3 roundPos = { center.x + 5.0f, 0.3f, center.z + 5.0f };
    DrawCylinderEx(roundPos, {roundPos.x, roundPos.y + 0.1f, roundPos.z}, 2.5f, 2.5f, 16, BLUE);
    DrawCube({roundPos.x, 1.0f, roundPos.z}, 0.2f, 1.5f, 0.2f, LIGHTGRAY);
    DrawCube({roundPos.x, 1.5f, roundPos.z}, 1.8f, 0.1f, 1.8f, YELLOW);
    // ENFANT près du tourniquet
    DrawChild({roundPos.x + 1.5f, 0.1f, roundPos.z + 1.0f}, GREEN, false);

    // Bancs de jardin
    DrawCube({center.x, 0.5f, center.z - groundSize/2 + 3.0f}, 4.0f, 0.1f, 1.0f, WOOD_COLOR); // Fond
    DrawCube({center.x - 7.0f, 0.5f, center.z + 2.0f}, 1.0f, 0.1f, 3.0f, WOOD_COLOR); // Côté gauche

    // --- FIN ROTATION ---
    rlPopMatrix();
}
// -----------------------------------------------------------------------------
//  ÉCOLE PRIMAIRE (ENTOURÉE D'ARBRES) 🏫🌳🇲🇦
// -----------------------------------------------------------------------------
inline void DrawSchool(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------

    // Dimensions
    float w = 28.0f; 
    float h = 8.0f;  
    float d = 10.0f; 

    Vector3 pos = position;

    // Couleurs
    Color SCHOOL_WALL = { 255, 230, 180, 255 }; 
    Color ROOF_COLOR = { 200, 100, 50, 255 };   
    Color GLASS = { 100, 200, 255, 150 };
    Color COURTYARD = { 180, 180, 180, 255 };   
    Color FENCE = { 50, 50, 50, 255 };
    
    // Couleurs Arbres
    Color TRUNK_BROWN = { 100, 60, 20, 255 };
    Color LEAVES_GREEN = { 30, 120, 30, 255 };
    Color LEAVES_LIGHT = { 80, 180, 50, 255 };

    // === HELPER : DESSINER UN ARBRE ===
    auto DrawTree = [&](float tx, float tz) {
        Vector3 tPos = { pos.x + tx, 0.0f, pos.z + tz };
        // Tronc
        DrawCylinderEx(tPos, {tPos.x, 2.5f, tPos.z}, 0.6f, 0.4f, 6, TRUNK_BROWN);
        // Feuillage (2 sphères)
        DrawSphere({tPos.x, 3.5f, tPos.z}, 2.0f, LEAVES_GREEN);
        DrawSphere({tPos.x, 4.8f, tPos.z}, 1.5f, LEAVES_LIGHT);
    };

    // ==========================================================
    // 1. LES ARBRES (AUTOUR DE L'ÉCOLE)
    // ==========================================================
    
    // Arrière du bâtiment (Ligne d'arbres)
    for (float x = -w/2 - 4.0f; x <= w/2 + 4.0f; x += 6.0f) {
        DrawTree(x, -d - 2.0f);
    }

    // Côté Gauche (Le long du bâtiment et de la cour)
    for (float z = -d; z <= 15.0f; z += 6.0f) {
        DrawTree(-w/2 - 5.0f, z);
    }

    // Côté Droit (Le long du bâtiment et de la cour)
    for (float z = -d; z <= 15.0f; z += 6.0f) {
        DrawTree(w/2 + 5.0f, z);
    }
    
    // Deux arbres devant l'entrée de la cour (coins)
    DrawTree(-w/2 - 2.0f, 16.0f);
    DrawTree(w/2 + 2.0f, 16.0f);


    // ==========================================================
    // 2. BÂTIMENTS (FORME EN U)
    // ==========================================================
    
    // --- Bloc Central ---
    Vector3 mainPos = { pos.x, h/2, pos.z - 6.0f };
    DrawCube(mainPos, w, h, d, SCHOOL_WALL);
    DrawCubeWires(mainPos, w, h, d, LIGHTGRAY);
    DrawCube({mainPos.x, h, mainPos.z}, w + 1.0f, 0.5f, d + 1.0f, ROOF_COLOR);

    // --- Aile Gauche ---
    Vector3 leftWing = { pos.x - w/2 + 3.5f, h/2, pos.z + 2.0f };
    DrawCube(leftWing, 7.0f, h, 10.0f, SCHOOL_WALL);
    DrawCube({leftWing.x, h, leftWing.z}, 7.5f, 0.5f, 10.5f, ROOF_COLOR);

    // --- Aile Droite ---
    Vector3 rightWing = { pos.x + w/2 - 3.5f, h/2, pos.z + 2.0f };
    DrawCube(rightWing, 7.0f, h, 10.0f, SCHOOL_WALL);
    DrawCube({rightWing.x, h, rightWing.z}, 7.5f, 0.5f, 10.5f, ROOF_COLOR);

    // ==========================================================
    // 3. FENÊTRES
    // ==========================================================
    for(float y : { 2.5f, 6.0f }) { 
        for(float x = -10.0f; x <= 10.0f; x += 4.0f) {
            DrawCube({pos.x + x, y, pos.z - 6.0f + d/2 + 0.1f}, 2.5f, 1.8f, 0.1f, GLASS);
        }
    }

    // ==========================================================
    // 4. ENTRÉE BÂTIMENT
    // ==========================================================
    Vector3 doorPos = { pos.x, 1.5f, pos.z - 1.0f }; 
    DrawCube(doorPos, 4.0f, 3.0f, 0.5f, ROOF_COLOR); 
    DrawCube({doorPos.x, 1.5f, doorPos.z + 0.1f}, 3.0f, 3.0f, 0.1f, DARKGRAY); 
    // Horloge
    DrawCylinderEx({pos.x, 5.0f, pos.z - 0.9f}, {pos.x, 5.0f, pos.z - 0.8f}, 1.0f, 1.0f, 12, WHITE);
    DrawCylinderEx({pos.x, 5.0f, pos.z - 0.8f}, {pos.x, 5.0f, pos.z - 0.75f}, 0.1f, 0.1f, 12, BLACK);

    // ==========================================================
    // 5. COUR DE RÉCRÉATION
    // ==========================================================
    float courtW = w;
    float courtD = 15.0f;
    Vector3 courtPos = { pos.x, 0.05f, pos.z + 5.0f };
    
    DrawCube(courtPos, courtW, 0.1f, courtD, COURTYARD);
    
    // Clôture
    for(float x = -courtW/2; x <= courtW/2; x += 2.0f) {
        if(abs(x) < 3.0f) continue; 
        DrawCube({pos.x + x, 1.0f, pos.z + 12.5f}, 0.2f, 2.0f, 0.2f, FENCE); 
    }
    DrawCube({pos.x - 8.5f, 1.8f, pos.z + 12.5f}, 11.0f, 0.1f, 0.1f, FENCE);
    DrawCube({pos.x + 8.5f, 1.8f, pos.z + 12.5f}, 11.0f, 0.1f, 0.1f, FENCE);

    // ==========================================================
    // 6. DRAPEAU (MAROC)
    // ==========================================================
    Vector3 flagPoleBase = { pos.x - 8.0f, 0.0f, pos.z + 5.0f }; 
    DrawCylinderEx(flagPoleBase, {flagPoleBase.x, 8.0f, flagPoleBase.z}, 0.1f, 0.1f, 8, LIGHTGRAY);
    DrawCube({flagPoleBase.x + 1.0f, 7.5f, flagPoleBase.z}, 2.0f, 1.2f, 0.05f, RED);
    DrawCube({flagPoleBase.x + 1.0f, 7.5f, flagPoleBase.z}, 0.4f, 0.4f, 0.06f, DARKGREEN);


    // ==========================================================
    // 7. ENSEIGNE "ECOLE"
    // ==========================================================
    Vector3 signPos = { pos.x, h + 1.5f, pos.z - 6.0f };
    
    // E
    DrawCube({signPos.x - 4.0f, signPos.y, signPos.z}, 0.3f, 1.5f, 0.3f, WHITE);
    DrawCube({signPos.x - 3.5f, signPos.y + 0.7f, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE);
    DrawCube({signPos.x - 3.5f, signPos.y, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE);
    DrawCube({signPos.x - 3.5f, signPos.y - 0.7f, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE);
    // C
    DrawCube({signPos.x - 2.0f, signPos.y, signPos.z}, 0.3f, 1.5f, 0.3f, WHITE);
    DrawCube({signPos.x - 1.5f, signPos.y + 0.7f, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE);
    DrawCube({signPos.x - 1.5f, signPos.y - 0.7f, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE);
    // O
    DrawCube({signPos.x + 0.0f, signPos.y, signPos.z}, 0.3f, 1.5f, 0.3f, WHITE); 
    DrawCube({signPos.x + 1.0f, signPos.y, signPos.z}, 0.3f, 1.5f, 0.3f, WHITE); 
    DrawCube({signPos.x + 0.5f, signPos.y + 0.7f, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE); 
    DrawCube({signPos.x + 0.5f, signPos.y - 0.7f, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE); 
    // L
    DrawCube({signPos.x + 2.5f, signPos.y, signPos.z}, 0.3f, 1.5f, 0.3f, WHITE);
    DrawCube({signPos.x + 3.0f, signPos.y - 0.7f, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE);
    // E
    DrawCube({signPos.x + 4.5f, signPos.y, signPos.z}, 0.3f, 1.5f, 0.3f, WHITE);
    DrawCube({signPos.x + 5.0f, signPos.y + 0.7f, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE);
    DrawCube({signPos.x + 5.0f, signPos.y, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE);
    DrawCube({signPos.x + 5.0f, signPos.y - 0.7f, signPos.z}, 1.0f, 0.3f, 0.3f, WHITE);

    // --- FIN ROTATION ---
    rlPopMatrix();
}
// -----------------------------------------------------------------------------
//  COMPLEXE PHARMACEUTIQUE (XXL - 6 ÉTAGES) 💊🏥
// -----------------------------------------------------------------------------
inline void DrawPharmacy(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------

    // --- NOUVELLES DIMENSIONS (XXL) ---
    float w = 20.0f;              // Largeur doublée
    float h = 24.0f;              // 6 Étages de 4m
    float d = 16.0f;              // Profondeur augmentée

    Vector3 pos = position;
    Vector3 centerPos = { pos.x, h/2.0f, pos.z };

    // Couleurs
    Color WALL_WHITE = { 245, 250, 250, 255 }; // Blanc clinique
    Color PHARMA_GREEN = { 0, 160, 50, 255 };  // Vert logo
    Color NEON_GREEN = { 50, 255, 50, 255 };   // Vert lumineux (Néon)
    Color GLASS = { 100, 220, 255, 140 };      // Verre bleuté
    Color METAL = { 180, 180, 190, 255 };      // Structure métal

    // ==========================================================
    // 1. STRUCTURE PRINCIPALE (La Tour)
    // ==========================================================
    DrawCube(centerPos, w, h, d, WALL_WHITE);
    DrawCubeWires(centerPos, w, h, d, LIGHTGRAY);

    // Cadre Vert géant qui fait le tour de la façade (Architecture moderne)
    // Côté Gauche
    DrawCube({pos.x - w/2 + 1.0f, h/2, pos.z + d/2 + 0.1f}, 2.0f, h, 0.5f, PHARMA_GREEN);
    // Côté Droit
    DrawCube({pos.x + w/2 - 1.0f, h/2, pos.z + d/2 + 0.1f}, 2.0f, h, 0.5f, PHARMA_GREEN);
    // Haut
    DrawCube({pos.x, h - 1.0f, pos.z + d/2 + 0.1f}, w, 2.0f, 0.5f, PHARMA_GREEN);

    // ==========================================================
    // 2. FAÇADE VITRÉE (MUR RIDEAU)
    // ==========================================================
    // Une immense vitre centrale qui couvre les étages 1 à 5
    Vector3 glassPos = { pos.x, (h/2.0f) + 2.0f, pos.z + d/2 };
    DrawCube(glassPos, w - 4.0f, h - 8.0f, 0.2f, GLASS);
    
    // Grille de séparation des vitres (Cadres)
    DrawCubeWires(glassPos, w - 4.0f, h - 8.0f, 0.2f, METAL);
    // Lignes horizontales pour marquer les étages
    for(float y = 4.0f; y < h - 4.0f; y += 4.0f) {
        DrawCube({pos.x, y, pos.z + d/2 + 0.1f}, w - 4.0f, 0.2f, 0.2f, METAL);
    }

    // ==========================================================
    // 3. REZ-DE-CHAUSSÉE (ACCUEIL & VENTE)
    // ==========================================================
    // Entrée large
    Vector3 entrancePos = { pos.x, 2.0f, pos.z + d/2 + 0.2f };
    DrawCube(entrancePos, w - 2.0f, 4.0f, 0.1f, GLASS); // Vitrine RDC
    
    // Portes coulissantes automatiques (Verre vert)
    DrawCube({pos.x, 2.0f, pos.z + d/2 + 0.3f}, 6.0f, 3.5f, 0.1f, NEON_GREEN); // Cadre néon
    DrawCube({pos.x, 2.0f, pos.z + d/2 + 0.35f}, 5.8f, 3.5f, 0.1f, GLASS);     // Portes

    // Auvent (Store) rigide moderne au dessus de l'entrée
    DrawCube({pos.x, 5.0f, pos.z + d/2 + 2.0f}, w, 0.5f, 4.0f, WALL_WHITE);
    // Dessous de l'auvent en vert
    DrawCube({pos.x, 4.9f, pos.z + d/2 + 2.0f}, w - 0.5f, 0.1f, 3.8f, PHARMA_GREEN);

    // ==========================================================
    // 4. CROIX VERTE MONUMENTALE (SUR LE TOIT)
    // ==========================================================
    // Structure métallique pour tenir la croix
    Vector3 roofBase = { pos.x, h + 2.0f, pos.z + d/2 - 2.0f };
    DrawCylinderEx({roofBase.x - 2.0f, h, roofBase.z}, {roofBase.x - 2.0f, h + 3.0f, roofBase.z}, 0.3f, 0.3f, 8, METAL);
    DrawCylinderEx({roofBase.x + 2.0f, h, roofBase.z}, {roofBase.x + 2.0f, h + 3.0f, roofBase.z}, 0.3f, 0.3f, 8, METAL);

    // La Croix (XXL)
    Vector3 crossPos = { pos.x, h + 3.5f, pos.z + d/2 - 2.0f };
    float cSize = 6.0f; // Immense (6 mètres)
    float cThick = 1.5f;

    // Barre Verticale
    DrawCube(crossPos, cThick, cSize, 0.5f, NEON_GREEN);
    // Barre Horizontale
    DrawCube(crossPos, cSize, cThick, 0.5f, NEON_GREEN);
    
    // Contour blanc pour faire ressortir
    DrawCubeWires(crossPos, cThick, cSize, 0.5f, WHITE);
    DrawCubeWires(crossPos, cSize, cThick, 0.5f, WHITE);

    // ==========================================================
    // 5. DÉCORATION LATÉRALE (GÉLULE GÉANTE)
    // ==========================================================
    // Sur le mur de côté, on dessine une gélule 3D
    Vector3 pillPos = { pos.x - w/2 - 0.5f, h - 8.0f, pos.z };
    
    // Moitié Blanche (Haut)
    DrawSphere({pillPos.x, pillPos.y + 1.5f, pillPos.z}, 2.0f, WHITE);
    DrawCylinderEx({pillPos.x, pillPos.y, pillPos.z}, {pillPos.x, pillPos.y + 1.5f, pillPos.z}, 2.0f, 2.0f, 16, WHITE);
    
    // Moitié Verte (Bas)
    DrawCylinderEx({pillPos.x, pillPos.y - 1.5f, pillPos.z}, {pillPos.x, pillPos.y, pillPos.z}, 2.0f, 2.0f, 16, PHARMA_GREEN);
    DrawSphere({pillPos.x, pillPos.y - 1.5f, pillPos.z}, 2.0f, PHARMA_GREEN);


    // ==========================================================
    // 6. INTÉRIEUR RDC (RAYONS)
    // ==========================================================
    // On voit à travers la vitrine
    for(float z = pos.z - d/2 + 2.0f; z < pos.z + d/2 - 4.0f; z += 3.0f) {
        // Rayonnages
        DrawCube({pos.x, 2.0f, z}, 12.0f, 2.5f, 0.5f, LIGHTGRAY);
        // Produits (Blocs colorés)
        DrawCube({pos.x - 3.0f, 2.5f, z + 0.3f}, 2.0f, 0.5f, 0.2f, WHITE);
        DrawCube({pos.x + 3.0f, 2.5f, z + 0.3f}, 2.0f, 0.5f, 0.2f, BLUE);
    }

    // --- FIN ROTATION ---
    rlPopMatrix();
}
inline void DrawBakery(Vector3 position, float rotationAngle = 0.0f)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);

    // --- NOUVELLES DIMENSIONS (XXL) ---
    float w = 20.0f; // Beaucoup plus large
    float h = 14.0f; // 2 Grands étages + Toit
    float d = 16.0f; 

    Vector3 pos = position;
    Vector3 centerPos = { pos.x, h/2.0f, pos.z };

    // Couleurs
    Color WALL_CREAM = { 255, 245, 220, 255 };
    Color WOOD_DARK = { 90, 50, 20, 255 };    
    Color BREAD_GOLD = { 255, 170, 40, 255 }; 
    Color AWNING_RED = { 160, 40, 40, 255 };
    Color GLASS = { 150, 200, 255, 150 };

    // 1. BÂTIMENT MASSIF
    DrawCube(centerPos, w, h, d, WALL_CREAM);
    DrawCubeWires(centerPos, w, h, d, WOOD_DARK);

    // 2. TOIT GÉANT
    // Un gros toit qui dépasse
    Vector3 roofPos = { pos.x, h, pos.z };
    DrawCube({roofPos.x, roofPos.y + 1.5f, roofPos.z}, w + 2.0f, 3.0f, d + 2.0f, WOOD_DARK);

    // 3. ÉTAGE (FENÊTRES)
    // 3 Grandes fenêtres à l'étage
    for(float x = -6.0f; x <= 6.0f; x += 6.0f) {
        DrawCube({pos.x + x, h - 4.0f, pos.z + d/2 + 0.1f}, 4.0f, 3.0f, 0.2f, GLASS);
        DrawCubeWires({pos.x + x, h - 4.0f, pos.z + d/2 + 0.1f}, 4.0f, 3.0f, 0.2f, WOOD_DARK);
    }

    // 4. REZ-DE-CHAUSSÉE (VITRINE)
    Vector3 shopFront = { pos.x, 3.0f, pos.z + d/2 + 0.1f };
    DrawCube(shopFront, w - 2.0f, 5.0f, 0.3f, GLASS);
    
    // Présentoir à pains (Plus rempli)
    for(float x = -8.0f; x <= 8.0f; x += 2.0f) {
        DrawCube({pos.x + x, 2.0f, pos.z + d/2 - 1.0f}, 1.0f, 0.5f, 0.5f, BREAD_GOLD);
        DrawCube({pos.x + x, 3.0f, pos.z + d/2 - 1.0f}, 0.8f, 0.8f, 0.5f, BREAD_GOLD);
    }

    // 5. STORE BANNE (AUVENT) IMMENSE
    DrawCube({pos.x, 6.5f, pos.z + d/2 + 1.5f}, w, 0.3f, 3.0f, AWNING_RED);
    // Bandes blanches
    for(float x = -w/2; x < w/2; x += 2.0f) {
        DrawCube({pos.x + x, 6.51f, pos.z + d/2 + 1.5f}, 1.0f, 0.3f, 3.0f, WHITE);
    }

    // 6. BAGUETTE GÉANTE (SCALE UP)
    Vector3 signPos = { pos.x, h + 3.0f, pos.z + d/2 };
    DrawCylinderEx({signPos.x - 6.0f, signPos.y, signPos.z}, {signPos.x + 6.0f, signPos.y, signPos.z}, 1.2f, 1.2f, 8, BREAD_GOLD);
    
    rlPopMatrix();
}
// -----------------------------------------------------------------------------
//  LABORATOIRE D'ANALYSES (MODERNE + TUBE À ESSAI GÉANT) 🔬🧪
// -----------------------------------------------------------------------------
inline void DrawLab(Vector3 position, float rotationAngle = 0.0f)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);

    // --- NOUVELLES DIMENSIONS (XXL) ---
    float w = 22.0f; 
    float floorH = 4.0f;
    int floors = 6;       // 6 Étages !
    float h = floors * floorH; 
    float d = 22.0f;      // Très profond (carré)

    Vector3 pos = position;
    Vector3 centerPos = { pos.x, h/2.0f, pos.z };

    // Couleurs
    Color LAB_WHITE = { 245, 245, 255, 255 };
    Color LAB_BLUE = { 0, 80, 180, 255 };
    Color GLASS_CYAN = { 100, 255, 255, 120 };
    Color LIQUID_PURPLE = { 180, 0, 255, 255 };
    Color METAL_GRAY = { 80, 80, 80, 255 };

    // 1. TOUR PRINCIPALE
    DrawCube(centerPos, w, h, d, LAB_WHITE);
    DrawCubeWires(centerPos, w, h, d, LIGHTGRAY);

    // Bande bleue géante sur toute la hauteur
    DrawCube({pos.x - w/2 + 3.0f, h/2, pos.z + d/2 + 0.1f}, 5.0f, h, 0.5f, LAB_BLUE);

    // 2. FENÊTRES (SUR 5 ÉTAGES)
    for (int i = 1; i < floors; i++) {
        float y = (i * floorH) + 2.0f;
        // Grande baie vitrée continue
        DrawCube({pos.x + 3.0f, y, pos.z + d/2 + 0.1f}, 12.0f, 2.5f, 0.1f, GLASS_CYAN);
        // Fenêtres côtés
        DrawCube({pos.x - w/2 - 0.1f, y, pos.z}, 0.1f, 2.5f, 18.0f, GLASS_CYAN);
        DrawCube({pos.x + w/2 + 0.1f, y, pos.z}, 0.1f, 2.5f, 18.0f, GLASS_CYAN);
    }

    // 3. ENTRÉE MONUMENTALE
    Vector3 doorPos = { pos.x + 3.0f, 2.5f, pos.z + d/2 + 0.5f };
    DrawCube(doorPos, 8.0f, 5.0f, 1.0f, METAL_GRAY);
    DrawCube({doorPos.x, doorPos.y, doorPos.z + 0.1f}, 6.0f, 4.0f, 0.1f, GLASS_CYAN);

    // 4. TUBE À ESSAI GÉANT (ENSEIGNE)
    // Il fait maintenant 10 mètres de haut !
    Vector3 tubePos = { pos.x - w/2 + 3.0f, h - 6.0f, pos.z + d/2 + 1.0f };
    
    DrawCylinderEx({tubePos.x, tubePos.y - 5.0f, tubePos.z}, {tubePos.x, tubePos.y + 5.0f, tubePos.z}, 1.2f, 1.2f, 12, GLASS_CYAN); // Verre
    DrawCylinderEx({tubePos.x, tubePos.y - 4.8f, tubePos.z}, {tubePos.x, tubePos.y + 2.0f, tubePos.z}, 1.0f, 1.0f, 12, LIQUID_PURPLE); // Liquide
    DrawCylinderEx({tubePos.x, tubePos.y + 5.0f, tubePos.z}, {tubePos.x, tubePos.y + 5.5f, tubePos.z}, 1.4f, 1.4f, 12, BLACK); // Bouchon

    // 5. CLIMATISATION TOIT
    DrawCube({pos.x, h + 2.0f, pos.z}, 10.0f, 4.0f, 10.0f, METAL_GRAY);

    rlPopMatrix();
}
//  CAFÉ "COZY" (AVEC TERRASSE, PARASOLS ET TASSE GÉANTE) ☕☀️
// -----------------------------------------------------------------------------
inline void DrawCafe(Vector3 position, float rotationAngle = 0.0f)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);

    // --- NOUVELLES DIMENSIONS (XXL) ---
    float w = 20.0f; 
    float h = 10.0f; // 2 Étages
    float d = 14.0f; 

    Vector3 pos = position;
    Vector3 centerPos = { pos.x, h/2.0f, pos.z };

    // Couleurs (J'ajoute WOOD_BROWN ici pour corriger l'erreur précédente)
    Color COFFEE_WALL = { 100, 70, 50, 255 }; 
    Color CREAM_ACCENT = { 240, 230, 200, 255 };
    Color PARASOL_RED = { 200, 50, 50, 255 };
    Color TABLE_WHITE = { 255, 255, 255, 255 };
    Color GLASS = { 50, 50, 50, 200 };
    Color WOOD_BROWN = { 110, 60, 20, 255 }; // <--- Définition ajoutée !

    // 1. BÂTIMENT (2 ÉTAGES)
    DrawCube(centerPos, w, h, d, COFFEE_WALL);
    
    // Bande de séparation entre les étages (Corniche)
    DrawCube({pos.x, h/2.0f, pos.z + d/2 + 0.1f}, w + 1.0f, 1.0f, 1.0f, CREAM_ACCENT);

    // Fenêtres Étage 1
    DrawCube({pos.x, h * 0.75f, pos.z + d/2 + 0.1f}, w - 2.0f, 3.0f, 0.2f, GLASS);
    
    // Vitrine RDC
    DrawCube({pos.x, h * 0.25f, pos.z + d/2 + 0.1f}, w - 2.0f, 3.5f, 0.2f, GLASS);

    // 2. LA TERRASSE GÉANTE
    float terraceD = 10.0f; 
    Vector3 terrPos = { pos.x, 0.1f, pos.z + d/2 + terraceD/2.0f };
    DrawCube(terrPos, w + 4.0f, 0.2f, terraceD, BEIGE); // Sol terrasse plus large que le batiment

    // 3. TABLES ET PARASOLS (DOUBLE RANGÉE)
    for(float z = -2.5f; z <= 2.5f; z += 5.0f) { // 2 Rangées en profondeur
        for(float x = -6.0f; x <= 6.0f; x += 4.0f) { // 4 Tables en largeur
            float tX = pos.x + x;
            float tZ = terrPos.z + z;

            // Table
            DrawCylinderEx({tX, 0.2f, tZ}, {tX, 1.0f, tZ}, 0.1f, 0.1f, 8, BLACK);
            DrawCylinderEx({tX, 1.0f, tZ}, {tX, 1.05f, tZ}, 1.4f, 1.4f, 12, TABLE_WHITE);
            // Parasol
            DrawLine3D({tX, 1.0f, tZ}, {tX, 4.0f, tZ}, BLACK);
            DrawCylinderEx({tX, 4.0f, tZ}, {tX, 5.0f, tZ}, 2.5f, 0.0f, 16, PARASOL_RED);
        }
    }

    // 4. TASSE GÉANTE (ENCORE PLUS GROSSE)
    Vector3 cupPos = { pos.x + 5.0f, h + 1.0f, pos.z };
    DrawCylinderEx(cupPos, {cupPos.x, cupPos.y + 3.0f, cupPos.z}, 2.5f, 2.5f, 16, WHITE); // Tasse
    DrawCylinderEx({cupPos.x, cupPos.y + 2.8f, cupPos.z}, {cupPos.x, cupPos.y + 2.9f, cupPos.z}, 2.3f, 2.3f, 16, BLACK); // Café

    // 5. MENU SUR TROTTOIR
    Vector3 menuPos = { pos.x - 6.0f, 0.8f, terrPos.z + terraceD/2 + 0.5f };
    DrawCube(menuPos, 1.2f, 1.6f, 0.1f, BLACK); 
    DrawCubeWires(menuPos, 1.2f, 1.6f, 0.1f, WOOD_BROWN);

    rlPopMatrix();
}

// -----------------------------------------------------------------------------
//  STADE DE FOOTBALL (TRIBUNES + PROJECTEURS + SCORE) ⚽🏟️
// -----------------------------------------------------------------------------
inline void DrawStadium(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------

    // --- DIMENSIONS ---
    // Le stade est très étendu au sol
    float fieldW = 30.0f; // Largeur terrain
    float fieldD = 46.0f; // Longueur terrain
    float standH = 10.0f; // Hauteur tribunes

    Vector3 pos = position;

    // Couleurs
    Color GRASS_GREEN = { 0, 140, 0, 255 };     // Pelouse
    Color LINE_WHITE = { 255, 255, 255, 200 };  // Lignes
    Color CONCRETE = { 180, 180, 180, 255 };    // Béton
    Color SEATS_RED = { 200, 50, 50, 255 };     // Sièges (Rouge)
    Color ROOF_WHITE = { 240, 240, 250, 255 };  // Toit
    Color POLE_GRAY = { 50, 50, 50, 255 };      // Poteaux

    // ==========================================================
    // 1. LE TERRAIN (PELOUSE)
    // ==========================================================
    // Base verte
    DrawCube({pos.x, 0.1f, pos.z}, fieldW, 0.2f, fieldD, GRASS_GREEN);
    
    // --- LIGNES BLANCHES ---
    float lineY = 0.25f;
    // Ligne médiane
    DrawCube({pos.x, lineY, pos.z}, fieldW, 0.05f, 0.3f, LINE_WHITE);
    // Rond central (simulé par un cube plat faute de cercle creux facile)
    DrawCube({pos.x, lineY, pos.z}, 6.0f, 0.05f, 0.3f, LINE_WHITE);
    DrawCube({pos.x, lineY, pos.z}, 0.3f, 0.05f, 6.0f, LINE_WHITE);
    
    // Surfaces de réparation (Buts)
    DrawCubeWires({pos.x, lineY, pos.z - fieldD/2 + 4.0f}, 12.0f, 0.05f, 8.0f, LINE_WHITE); // Nord
    DrawCubeWires({pos.x, lineY, pos.z + fieldD/2 - 4.0f}, 12.0f, 0.05f, 8.0f, LINE_WHITE); // Sud

    // ==========================================================
    // 2. LES BUTS (CAGES)
    // ==========================================================
    // But Nord
    Vector3 goalN = { pos.x, 1.5f, pos.z - fieldD/2 + 0.5f };
    DrawCubeWires(goalN, 5.0f, 2.5f, 1.0f, WHITE);
    // But Sud
    Vector3 goalS = { pos.x, 1.5f, pos.z + fieldD/2 - 0.5f };
    DrawCubeWires(goalS, 5.0f, 2.5f, 1.0f, WHITE);

    // ==========================================================
    // 3. LES TRIBUNES (GRADINS) - GAUCHE ET DROITE
    // ==========================================================
    float standWidth = 10.0f; // Profondeur des gradins
    
    // On boucle pour faire les 2 côtés (x = -1 pour gauche, x = 1 pour droite)
    for(int side : {-1, 1}) {
        float dir = (float)side;
        float centerX = pos.x + (dir * (fieldW/2 + standWidth/2));
        
        // Structure béton extérieur (Le mur arrière)
        DrawCube({centerX, standH/2, pos.z}, standWidth, standH, fieldD, CONCRETE);
        
        // Les sièges (Escaliers)
        // On dessine 5 grosses marches
        for(int i = 0; i < 5; i++) {
            float stepY = 1.5f + (i * 1.5f);
            float stepX = pos.x + (dir * (fieldW/2 + i * 1.5f + 1.0f));
            
            // Sièges Rouges
            DrawCube({stepX, stepY, pos.z}, 1.5f, 0.5f, fieldD - 2.0f, SEATS_RED);
        }

        // Le Toit (Suspendu)
        Vector3 roofPos = { centerX - (dir * 2.0f), standH + 4.0f, pos.z };
        DrawCube(roofPos, standWidth + 4.0f, 0.5f, fieldD + 2.0f, ROOF_WHITE);
        
        // Piliers de soutien du toit (arrière)
        for(float z = -fieldD/2; z <= fieldD/2; z += 10.0f) {
            DrawCylinderEx({centerX + (dir * 4.0f), 0.0f, pos.z + z}, 
                           {centerX + (dir * 4.0f), standH + 4.0f, pos.z + z}, 
                           0.5f, 0.5f, 6, POLE_GRAY);
        }
    }

    // ==========================================================
    // 4. LES PROJECTEURS (FLOODLIGHTS) 💡
    // ==========================================================
    // Aux 4 coins du terrain
    float poleH = 20.0f; // Très haut
    for(int sx : {-1, 1}) {
        for(int sz : {-1, 1}) {
            Vector3 polePos = { pos.x + (sx * (fieldW/2 + 2.0f)), 0.0f, pos.z + (sz * (fieldD/2 + 2.0f)) };
            
            // Le poteau
            DrawCylinderEx(polePos, {polePos.x, poleH, polePos.z}, 0.4f, 0.2f, 8, POLE_GRAY);
            
            // Le panneau de lumières (Rectangle blanc brillant en haut)
            // On l'oriente vers le centre du terrain (simplifié ici juste face z)
            DrawCube({polePos.x, poleH, polePos.z}, 3.0f, 2.0f, 0.5f, WHITE);
        }
    }

    // ==========================================================
    // 5. TABLEAU D'AFFICHAGE (SCOREBOARD)
    // ==========================================================
    // Placé derrière le but Nord
    Vector3 boardPos = { pos.x, 8.0f, pos.z - fieldD/2 - 4.0f };
    
    // Piliers
    DrawCylinderEx({boardPos.x - 3.0f, 0.0f, boardPos.z}, {boardPos.x - 3.0f, 8.0f, boardPos.z}, 0.3f, 0.3f, 6, POLE_GRAY);
    DrawCylinderEx({boardPos.x + 3.0f, 0.0f, boardPos.z}, {boardPos.x + 3.0f, 8.0f, boardPos.z}, 0.3f, 0.3f, 6, POLE_GRAY);
    
    // Écran
    DrawCube(boardPos, 10.0f, 4.0f, 0.5f, BLACK);     // Cadre
    DrawCube({boardPos.x, boardPos.y, boardPos.z + 0.1f}, 9.0f, 3.0f, 0.1f, DARKBLUE); // Écran allumé
    
    // Score (Simulé par des cubes jaunes)
    // "1 - 0"
    DrawCube({boardPos.x - 2.0f, boardPos.y, boardPos.z + 0.2f}, 0.5f, 1.5f, 0.1f, YELLOW); // 1
    DrawCube({boardPos.x, boardPos.y, boardPos.z + 0.2f}, 0.5f, 0.5f, 0.1f, YELLOW);        // -
    DrawCubeWires({boardPos.x + 2.0f, boardPos.y, boardPos.z + 0.2f}, 1.0f, 1.5f, 0.1f, YELLOW); // 0 (Carré vide)


    // --- FIN ROTATION ---
    rlPopMatrix();
}

// -----------------------------------------------------------------------------
//  CINÉMA (AVEC POP-CORN GÉANT ET TAPIS ROUGE) 🎬🍿
// -----------------------------------------------------------------------------
inline void DrawCinema(Vector3 position, float rotationAngle = 0.0f)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);

    // --- DIMENSIONS XXL ---
    float w = 34.0f; // Très large (Façade imposante)
    float h = 18.0f; // Haut comme un immeuble de 4 étages
    float d = 24.0f; // Profond pour les salles

    Vector3 pos = position;
    Vector3 centerPos = { pos.x, h/2.0f, pos.z };

    // Couleurs
    Color WALL_BLUE = { 20, 20, 70, 255 };      // Bleu nuit profond
    Color ACCENT_GOLD = { 255, 215, 0, 255 };   // Or brillant
    Color CARPET_RED = { 220, 20, 20, 255 };    // Tapis Rouge
    Color POSTER_1 = { 50, 200, 100, 255 };     
    Color POSTER_2 = { 200, 100, 200, 255 };    
    Color POSTER_3 = { 50, 100, 200, 255 };
    Color NEON_LIGHT = { 200, 240, 255, 255 };  // Lumière blanche

    // 1. BÂTIMENT PRINCIPAL
    DrawCube(centerPos, w, h, d, WALL_BLUE);
    
    // Décoration Art Déco (Colonnes dorées sur la façade)
    DrawCube({pos.x - w/2, h/2, pos.z + d/2 + 0.1f}, 2.0f, h, 0.5f, ACCENT_GOLD);
    DrawCube({pos.x + w/2, h/2, pos.z + d/2 + 0.1f}, 2.0f, h, 0.5f, ACCENT_GOLD);
    DrawCube({pos.x, h - 1.0f, pos.z + d/2 + 0.1f}, w, 2.0f, 0.5f, ACCENT_GOLD); // Corniche or

    // 2. ENTRÉE MAJESTUEUSE
    Vector3 entrancePos = { pos.x, 4.0f, pos.z + d/2 + 1.5f };
    // Auvent géant
    DrawCube(entrancePos, 14.0f, 1.5f, 4.0f, ACCENT_GOLD);
    // Panneau lumineux sous l'auvent ("NOW SHOWING")
    DrawCube({entrancePos.x, entrancePos.y - 0.8f, entrancePos.z}, 13.0f, 0.2f, 3.0f, NEON_LIGHT);
    
    // Tapis rouge (plus long)
    DrawCube({pos.x, 0.1f, pos.z + d/2 + 3.0f}, 8.0f, 0.1f, 8.0f, CARPET_RED);

    // 3. AFFICHES DE FILMS (GÉANTES - 3 affiches)
    float posterW = 6.0f;
    float posterH = 8.0f;
    // Gauche
    DrawCube({pos.x - 10.0f, 8.0f, pos.z + d/2 + 0.1f}, posterW, posterH, 0.2f, POSTER_1);
    DrawCubeWires({pos.x - 10.0f, 8.0f, pos.z + d/2 + 0.1f}, posterW, posterH, 0.2f, ACCENT_GOLD);
    // Droite
    DrawCube({pos.x + 10.0f, 8.0f, pos.z + d/2 + 0.1f}, posterW, posterH, 0.2f, POSTER_2);
    DrawCubeWires({pos.x + 10.0f, 8.0f, pos.z + d/2 + 0.1f}, posterW, posterH, 0.2f, ACCENT_GOLD);
    // Centre Haut
    DrawCube({pos.x, 12.0f, pos.z + d/2 + 0.1f}, posterW, posterH, 0.2f, POSTER_3);
    DrawCubeWires({pos.x, 12.0f, pos.z + d/2 + 0.1f}, posterW, posterH, 0.2f, ACCENT_GOLD);

    // 4. POT DE POP-CORN MONUMENTAL (TOIT) 🍿
    // Il fait maintenant 8 mètres de haut !
    Vector3 popPos = { pos.x - 8.0f, h + 4.0f, pos.z - 4.0f };
    
    // Le Pot
    DrawCylinderEx({popPos.x, popPos.y - 4.0f, popPos.z}, {popPos.x, popPos.y + 4.0f, popPos.z}, 3.5f, 4.5f, 20, WHITE);
    
    // Rayures rouges
    for(int i=0; i<360; i+=30) { // Plus de rayures
        rlPushMatrix();
        rlTranslatef(popPos.x, popPos.y, popPos.z);
        rlRotatef(i, 0, 1, 0);
        DrawCube({4.0f, 0.0f, 0.0f}, 0.8f, 8.0f, 0.2f, CARPET_RED);
        rlPopMatrix();
    }
    
    // Les Pop-corns (Sphères géantes)
    for(int i=0; i<15; i++) {
        float px = ((i % 5) - 2) * 1.5f;
        float pz = ((i / 5) - 1) * 1.5f;
        DrawSphere({popPos.x + px, popPos.y + 4.0f + (i%3)*0.8f, popPos.z + pz}, 1.2f, ACCENT_GOLD);
    }

    rlPopMatrix();
}
// -----------------------------------------------------------------------------
//  FAST FOOD "BURGER KING" STYLE (AVEC BURGER GÉANT) 🍔🍟
// -----------------------------------------------------------------------------
inline void DrawBurgerShop(Vector3 position, float rotationAngle = 0.0f)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);

    // --- DIMENSIONS XXL ---
    float w = 24.0f; 
    float h = 12.0f; // 2 Étages (RDC + Étage salle)
    float d = 18.0f; 

    Vector3 pos = position;

    // Couleurs
    Color DINER_RED = { 220, 20, 20, 255 };
    Color DINER_WHITE = { 255, 255, 255, 255 };
    Color GLASS = { 100, 200, 255, 150 };
    // Burger
    Color BUN_COLOR = { 230, 170, 80, 255 };
    Color MEAT_COLOR = { 90, 40, 10, 255 };
    Color SALAD_COLOR = { 50, 200, 50, 255 };
    Color CHEESE_COLOR = { 255, 220, 0, 255 };

    // 1. RDC (Cuisine et commande)
    DrawCube({pos.x, 3.0f, pos.z}, w, 6.0f, d, DINER_RED);
    // Vitres RDC
    DrawCube({pos.x, 3.0f, pos.z + d/2 + 0.1f}, w - 2.0f, 4.0f, 0.2f, GLASS);

    // 2. ÉTAGE (Salle à manger vue panoramique)
    // Un peu plus petit pour créer une terrasse
    DrawCube({pos.x, 9.0f, pos.z}, w - 2.0f, 6.0f, d - 2.0f, DINER_WHITE);
    // Vitres Étage (Tout le tour)
    DrawCube({pos.x, 9.0f, pos.z}, w - 2.5f, 4.0f, d - 2.5f, GLASS); 
    // Piliers de coins pour tenir les vitres
    DrawCubeWires({pos.x, 9.0f, pos.z}, w - 2.0f, 6.0f, d - 2.0f, DINER_RED);

    // 3. BANDEAU DE DÉCORATION
    // Entre le RDC et l'étage
    DrawCube({pos.x, 6.0f, pos.z}, w + 1.0f, 1.0f, d + 1.0f, DINER_WHITE);

    // 4. LE BURGER COLOSSAL (SUR LE TOIT)
    // Il est deux fois plus gros qu'avant !
    Vector3 bPos = { pos.x, h + 1.0f, pos.z }; 
    float r = 5.0f; // Rayon de 5 unités (énorme)

    // Pain bas
    DrawCylinderEx(bPos, {bPos.x, bPos.y + 2.0f, bPos.z}, r, r, 20, BUN_COLOR);
    // Viande (Steak épais)
    DrawCylinderEx({bPos.x, bPos.y + 2.0f, bPos.z}, {bPos.x, bPos.y + 3.5f, bPos.z}, r + 0.2f, r + 0.2f, 20, MEAT_COLOR);
    // Fromage (Carré qui coule)
    DrawCube({bPos.x, bPos.y + 3.6f, bPos.z}, r * 2.2f, 0.4f, r * 2.2f, CHEESE_COLOR);
    // Salade
    DrawCylinderEx({bPos.x, bPos.y + 3.8f, bPos.z}, {bPos.x, bPos.y + 4.5f, bPos.z}, r + 0.5f, r + 0.5f, 20, SALAD_COLOR);
    // Pain haut (Dôme)
    DrawCylinderEx({bPos.x, bPos.y + 4.5f, bPos.z}, {bPos.x, bPos.y + 7.0f, bPos.z}, r, r * 0.7f, 20, BUN_COLOR);
    DrawSphere({bPos.x, bPos.y + 7.0f, bPos.z}, r * 0.7f, BUN_COLOR);

    // Sésames géants
    for(int i=0; i<8; i++) {
        DrawCube({bPos.x + (i%2?1:-1)*2.0f, bPos.y + 8.0f, bPos.z + (i/2?1:-1)*2.0f}, 0.5f, 0.3f, 0.5f, WHITE);
    }

    rlPopMatrix();
}
// -----------------------------------------------------------------------------
//  GRANDE FONTAINE CENTRALE (POUR ROND-POINT) ⛲💧
// -----------------------------------------------------------------------------
inline void DrawFountain(Vector3 position)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    
    // Pas de rotation nécessaire car c'est un cercle, 
    // mais on décale pour centrer le dessin sur la position donnée
    // (Si tu veux qu'elle soit posée au sol à y=0)

    Vector3 pos = { 0.0f, 0.0f, 0.0f }; // On travaille en local

    // --- COULEURS ---
    Color STONE_WHITE = { 230, 230, 235, 255 }; // Pierre blanche/Marbre
    Color STONE_GRAY = { 180, 180, 190, 255 };  // Pierre plus sombre
    Color WATER_BLUE = { 0, 120, 200, 200 };    // Eau du bassin (Transparente)
    Color WATER_FOAM = { 200, 240, 255, 120 };  // Écume / Jet (Très transparent)

    // 1. LE GRAND BASSIN (SOCLE)
    // Rayon de 7.0 (donc 14m de large), parfait pour un rond-point
    // Bordure en pierre
    DrawCylinder(pos, 7.2f, 7.2f, 0.8f, 32, STONE_GRAY); 
    // L'eau à l'intérieur (légèrement plus petite et plus haute)
    DrawCylinder({pos.x, 0.6f, pos.z}, 6.8f, 6.8f, 0.1f, 32, WATER_BLUE);

    // 2. NIVEAU 1 (PILLIER LARGE)
    DrawCylinder({pos.x, 0.8f, pos.z}, 3.0f, 3.5f, 1.5f, 24, STONE_WHITE);
    // Petite vasque intermédiaire
    DrawCylinder({pos.x, 2.3f, pos.z}, 4.0f, 0.5f, 0.5f, 24, STONE_WHITE);
    // Eau dans la vasque
    DrawCylinder({pos.x, 2.6f, pos.z}, 3.8f, 0.0f, 0.1f, 24, WATER_BLUE);

    // 3. NIVEAU 2 (PILLIER MOYEN)
    DrawCylinder({pos.x, 2.3f, pos.z}, 1.5f, 1.5f, 2.0f, 16, STONE_WHITE);
    // Vasque haute
    DrawCylinder({pos.x, 4.3f, pos.z}, 2.5f, 0.2f, 0.5f, 16, STONE_WHITE);
    
    // 4. LE JET D'EAU CENTRAL (GEYSER)
    // Cœur du jet (Dense)
    DrawCylinder({pos.x, 4.5f, pos.z}, 0.4f, 0.8f, 4.0f, 16, WATER_FOAM);
    // Retombée de l'eau (Cône plus large et transparent)
    DrawCylinder({pos.x, 4.0f, pos.z}, 0.0f, 3.0f, 3.5f, 16, WATER_FOAM);

    // 5. JETS SECONDAIRES (PETITS JETS AUTOUR)
    // On en place 4 autour du centre pour faire joli
    for(int i = 0; i < 360; i += 90) {
        float rad = 4.5f; // Distance du centre
        float angleRad = i * DEG2RAD; // Conversion deg->rad (approx)
        // Note: en C++ pur -> i * (PI/180.0f)
        
        float jx = sinf(i * (PI/180.0f)) * rad;
        float jz = cosf(i * (PI/180.0f)) * rad;

        // Le petit jet qui part du bassin vers le centre
        // On simule une parabole avec un cylindre incliné ou juste droit
        DrawCylinder({jx, 0.6f, jz}, 0.2f, 0.4f, 2.0f, 8, WATER_FOAM);
    }

    rlPopMatrix();
}
// -----------------------------------------------------------------------------
//  GRAND HÔTEL DE LUXE "ROYAL PALACE" (7 ÉTOILES ⭐ VIP) 🏨🥂
// -----------------------------------------------------------------------------
inline void DrawGrandHotel(Vector3 position, float rotationAngle = 0.0f)
{
    // --- DÉBUT ROTATION ---
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotationAngle, 0, 1, 0); 
    rlTranslatef(-position.x, -position.y, -position.z);
    // -----------------------

    Vector3 pos = position;

    // --- DIMENSIONS XXL (Gratte-ciel) ---
    float baseW = 28.0f; float baseD = 22.0f; float baseH = 6.0f; // Le Hall (RDC haut)
    float towerW = 22.0f; float towerD = 18.0f;
    int numFloors = 10;
    float floorH = 3.0f;
    float towerTotalH = numFloors * floorH; // 30m de tour
    float totalH = baseH + towerTotalH + 4.0f; // + Toit

    // --- COULEURS LUXE ---
    Color WALL_MARBLE = { 250, 245, 235, 255 }; // Blanc cassé/Crème riche
    Color GOLD_LUX = { 218, 165, 32, 255 };     // Or métallique
    Color GLASS_DARK = { 40, 60, 90, 220 };     // Vitres teintées foncées
    Color CARPET_RED = { 180, 10, 30, 255 };    // Rouge royal
    Color POOL_WATER = { 0, 180, 255, 200 };    // Eau piscine rooftop

    // ==========================================================
    // 1. LA BASE (LE LOBBY MAJESTUEUX)
    // ==========================================================
    Vector3 baseCenter = { pos.x, baseH/2.0f, pos.z };
    DrawCube(baseCenter, baseW, baseH, baseD, WALL_MARBLE);
    // Bordures dorées
    DrawCubeWires(baseCenter, baseW, baseH, baseD, GOLD_LUX);

    // Grandes baies vitrées du lobby (façade avant)
    DrawCube({pos.x, baseH/2.0f, pos.z + baseD/2 + 0.1f}, baseW - 4.0f, baseH - 1.0f, 0.1f, GLASS_DARK);
    // Piliers dorés en façade
    for(float x : {-baseW/2+1, -baseW/4, baseW/4, baseW/2-1}) {
         DrawCube({pos.x + x, baseH/2.0f, pos.z + baseD/2 + 0.2f}, 1.0f, baseH, 0.5f, GOLD_LUX);
    }

    // ==========================================================
    // 2. LA TOUR PRINCIPALE (LES CHAMBRES)
    // ==========================================================
    float currentY = baseH;
    
    for(int i = 0; i < numFloors; i++) {
        float yPos = currentY + floorH/2.0f;
        
        // Structure de l'étage (Marbre)
        DrawCube({pos.x, yPos, pos.z}, towerW, floorH, towerD, WALL_MARBLE);
        
        // Fenêtres continues (Mur rideau sur la façade avant)
        DrawCube({pos.x, yPos, pos.z + towerD/2 + 0.1f}, towerW - 2.0f, floorH - 0.5f, 0.1f, GLASS_DARK);
        
        // Bandeaux horizontaux dorés entre chaque étage
        DrawCube({pos.x, currentY, pos.z}, towerW + 0.5f, 0.5f, towerD + 0.5f, GOLD_LUX);

        // Balcons VIP (Un étage sur deux sur les côtés)
        if(i % 2 != 0) {
            // Gauche
            DrawCube({pos.x - towerW/2 - 1.0f, currentY + 0.2f, pos.z}, 2.0f, 0.2f, towerD - 4.0f, WALL_MARBLE); // Sol
            DrawCubeWires({pos.x - towerW/2 - 1.0f, yPos, pos.z}, 2.0f, floorH-0.2f, towerD - 4.0f, GOLD_LUX); // Garde-corps or
            // Droite
            DrawCube({pos.x + towerW/2 + 1.0f, currentY + 0.2f, pos.z}, 2.0f, 0.2f, towerD - 4.0f, WALL_MARBLE);
            DrawCubeWires({pos.x + towerW/2 + 1.0f, yPos, pos.z}, 2.0f, floorH-0.2f, towerD - 4.0f, GOLD_LUX);
        }
        
        currentY += floorH;
    }

    // ==========================================================
    // 3. LE ROOFTOP (COURONNE & PISCINE) 👑
    // ==========================================================
    float roofY = baseH + towerTotalH;
    // Base du toit (plus large, corniche dorée)
    DrawCube({pos.x, roofY + 1.0f, pos.z}, towerW + 2.0f, 2.0f, towerD + 2.0f, WALL_MARBLE);
    DrawCube({pos.x, roofY + 2.0f, pos.z}, towerW + 3.0f, 0.5f, towerD + 3.0f, GOLD_LUX);

    // Piscine à débordement sur le devant du toit
    DrawCube({pos.x, roofY + 2.1f, pos.z + towerD/2 - 2.0f}, towerW - 4.0f, 0.8f, 4.0f, POOL_WATER);
    
    // Petit lounge couvert sur l'arrière du toit
    DrawCube({pos.x, roofY + 3.5f, pos.z - 3.0f}, towerW - 6.0f, 0.2f, 6.0f, GOLD_LUX); // Toit du lounge
    // Piliers du lounge
    DrawCylinderEx({pos.x - 5.0f, roofY+2.0f, pos.z-5.0f}, {pos.x - 5.0f, roofY+3.5f, pos.z-5.0f}, 0.3f, 0.3f, 6, GOLD_LUX);
    DrawCylinderEx({pos.x + 5.0f, roofY+2.0f, pos.z-5.0f}, {pos.x + 5.0f, roofY+3.5f, pos.z-5.0f}, 0.3f, 0.3f, 6, GOLD_LUX);

    // ==========================================================
    // 4. ENTRÉE VIP (PORTE-COCHÈRE & TAPIS ROUGE) 🚗
    // ==========================================================
    Vector3 entrancePos = { pos.x, baseH/2.0f - 1.0f, pos.z + baseD/2 + 3.0f };
    // Auvent géant doré supporté par des colonnes
    DrawCube({entrancePos.x, 4.5f, entrancePos.z}, baseW - 8.0f, 1.0f, 6.0f, GOLD_LUX);
    // Piliers de l'auvent
    DrawCylinderEx({entrancePos.x - 6.0f, 0.0f, entrancePos.z + 2.5f}, {entrancePos.x - 6.0f, 4.5f, entrancePos.z + 2.5f}, 0.8f, 0.8f, 12, GOLD_LUX);
    DrawCylinderEx({entrancePos.x + 6.0f, 0.0f, entrancePos.z + 2.5f}, {entrancePos.x + 6.0f, 4.5f, entrancePos.z + 2.5f}, 0.8f, 0.8f, 12, GOLD_LUX);
    
    // Tapis rouge royal qui sort de l'hôtel
    DrawCube({pos.x, 0.1f, pos.z + baseD/2 + 4.0f}, 6.0f, 0.1f, 10.0f, CARPET_RED);

    // ==========================================================
    // 5. ENSEIGNE "7 ÉTOILES" ⭐⭐⭐⭐⭐⭐⭐
    // ==========================================================
    // Placées très haut sur la façade de la tour
    float starY = roofY - 2.0f;
    float starZ = pos.z + towerD/2 + 0.6f;
    for(int i = 0; i < 7; i++) {
        float starX = pos.x + (i * 1.5f) - (3.0f * 1.5f); // Centrer les 7 étoiles
        // Simuler une étoile par un petit cube doré brillant (ou une sphère)
        DrawSphere({starX, starY, starZ}, 0.5f, GOLD_LUX);
    }
    // Petit panneau "VIP" dessous
    DrawCube({pos.x, starY - 1.5f, starZ}, 4.0f, 1.0f, 0.1f, GOLD_LUX);

    // --- FIN ROTATION ---
    rlPopMatrix();
}

#endif