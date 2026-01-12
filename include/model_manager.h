#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "raylib.h"
#include <map>
#include <string>

class ModelManager {
private:
    std::map<std::string, Model> models;
    
public:
    ModelManager();
    ~ModelManager();
    
    // Load all vehicle models
    void LoadModels();
    
    // Get a specific model by type
    Model& GetModel(const std::string& type);
    
    // Cleanup
    void UnloadModels();
};

#endif