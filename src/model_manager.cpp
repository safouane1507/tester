#include "model_manager.h"
#include <iostream>

ModelManager::ModelManager() {}

ModelManager::~ModelManager() {
    UnloadModels();
}

void ModelManager::LoadModels() {
    // Load all vehicle models
    models["Car"] = LoadModel("assets/models/car.glb");
    models["Bus"] = LoadModel("assets/models/bus.glb");
    models["Truck"] = LoadModel("assets/models/truck.glb");
    models["Taxi"] = LoadModel("assets/models/taxi.glb");
    models["Police"] = LoadModel("assets/models/police.glb");
    models["Motorcycle"] = LoadModel("assets/models/moto.glb");
    
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