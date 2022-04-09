#include "CameraManager.h"

bool CameraManager::Initialize() {
	camera->SetView(SimpleMath::Vector3(0.0f, 0.0f, 0.0f), SimpleMath::Vector3::Zero);
}

int CameraManager::Update(const float deltaTime) {

}

void CameraManager::Render() {
	DXTK->Direct3D9->SetCamera(camera);
}
