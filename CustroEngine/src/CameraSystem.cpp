#include "CameraSystem.h"

CameraSystem::CameraSystem()
{
    DefaultCamera = new CameraComponent();
    DefaultCamera->GetWorldTransform().SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    SetActiveCamera(DefaultCamera);
}

CameraSystem::~CameraSystem()
{
    delete DefaultCamera;
}

void CameraSystem::SetActiveCamera(CameraComponent* camera)
{
    ActiveCamera = camera;
    
    if (!camera)
        ActiveCamera = DefaultCamera;
}

void CameraSystem::AddActiveCamera(CameraComponent* camera)
{
    ActiveCameras.push_back(camera);
}

void CameraSystem::RemoveActiveCamera(CameraComponent* camera)
{
    ActiveCameras.erase(std::remove(ActiveCameras.begin(), ActiveCameras.end(), camera), ActiveCameras.end());
}
