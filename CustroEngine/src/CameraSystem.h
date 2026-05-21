#pragma once
#include <vector>

#include "Gameplay/Components/EntityComponents/SpatialComponents/CameraComponent.h"

class CameraSystem
{
public:
    static CameraSystem& Get()
    {
        static CameraSystem instance;
        return instance;
    }
    
    void SetActiveCamera(CameraComponent* camera);
    
    void AddActiveCamera(CameraComponent* camera);
    void RemoveActiveCamera(CameraComponent* camera);
    
    CameraComponent* GetActiveCamera() const { return ActiveCamera; }
    
private:
    CameraSystem();
    ~CameraSystem();
    
    CameraComponent* ActiveCamera;
    CameraComponent* DefaultCamera;
    
    std::pmr::vector<CameraComponent*> ActiveCameras;
    
    
};
