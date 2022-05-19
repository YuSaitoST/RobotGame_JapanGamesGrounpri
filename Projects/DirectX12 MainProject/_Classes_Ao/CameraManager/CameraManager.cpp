#include "CameraManager.h"

void CameraManager::Initialize() {
}

void CameraManager::Update() {
}

void CameraManager::Render() {
	DXTK->Direct3D9->SetCamera(camera);

}
