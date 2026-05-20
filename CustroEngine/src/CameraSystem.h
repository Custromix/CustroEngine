#pragma once
#include <vector>

#include "Gameplay/Components/EntityComponents/SpatialComponents/CameraComponent.h"

class CameraSystem
{
public:
    CameraSystem();
    ~CameraSystem();
    
    static void SetActiveCamera(CameraComponent* camera) { ActiveCamera = camera; }
    
    static void AddActiveCamera(CameraComponent* camera);
    static void RemoveActiveCamera(CameraComponent* camera);
    
    static CameraComponent* GetActiveCamera() { return ActiveCamera; }
    
private:
    
    static CameraComponent* ActiveCamera;
    
    static std::pmr::vector<CameraComponent*> ActiveCameras;
    
};
