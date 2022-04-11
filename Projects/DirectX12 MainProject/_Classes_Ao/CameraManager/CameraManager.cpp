#include "CameraManager.h"

void CameraManager::Initialize() {
	camera->SetView(SimpleMath::Vector3(3.0f, 2.5f, -10), SimpleMath::Vector3(0, 0, 0));
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
	DXTK->Direct3D9->SetCamera(camera);
}

void CameraManager::Update() {
	camera->SetPosition(player_.GetPlayer_Pos());
}

void CameraManager::Render() {
	DXTK->Direct3D9->SetCamera(camera);

}
