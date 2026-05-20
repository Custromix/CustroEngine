#include "CameraSystem.h"

CameraComponent* CameraSystem::ActiveCamera;
std::pmr::vector<CameraComponent*> CameraSystem::ActiveCameras;

CameraSystem::CameraSystem()
{
}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::AddActiveCamera(CameraComponent* camera)
{
    ActiveCameras.push_back(camera);
}

void CameraSystem::RemoveActiveCamera(CameraComponent* camera)
{
    ActiveCameras.erase(std::remove(ActiveCameras.begin(), ActiveCameras.end(), camera), ActiveCameras.end());
}
