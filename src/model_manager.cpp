#include "model_manager.h"
#include <iostream>

ModelManager::ModelManager() {}

ModelManager::~ModelManager() {
    UnloadModels();
}

void ModelManager::LoadModels() {
    // Load all vehicle models
    models["Car"] = LoadModel("assets/models/car.glb");         // Length =  6.27
    models["Bus"] = LoadModel("assets/models/bus.glb");         // Length = 11.80
    models["Truck"] = LoadModel("assets/models/truck.glb");     // Length = 14.50
    models["Taxi"] = LoadModel("assets/models/taxi.glb");       // Length =  7.09
    models["Police"] = LoadModel("assets/models/police.glb");   // Length =  6.96
    models["Motorcycle"] = LoadModel("assets/models/moto.glb"); // Length =  3.60
    
    std::cout << "[ModelManager] All models loaded successfully." << std::endl;
}

Model& ModelManager::GetModel(const std::string& type) {
    // Safety check
    if (models.find(type) == models.end()) {
        std::cerr << "[ERROR] Model not found: " << type << std::endl;
        return models["Car"]; // Fallback
    }
    return models[type];
}

void ModelManager::UnloadModels() {
    for (auto& pair : models) {
        UnloadModel(pair.second);
    }
    models.clear();
}