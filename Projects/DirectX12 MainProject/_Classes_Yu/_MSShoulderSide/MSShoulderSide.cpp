#include "MSShoulderSide.h"

void MSShoulderSide::Initialize(/*float* rotX, float* rotY*/) {
	//rotateX_ = *rotX;
	//rotateY_ = *rotY;
}

void MSShoulderSide::LoadAsset(std::wstring fileName) {
	shoulder_ = DX9::Model::CreateFromFile(DXTK->Device9, fileName.c_str());
}

void MSShoulderSide::Render(DirectX::SimpleMath::Vector3 playerPos, DirectX::SimpleMath::Vector3 shoulderForward) {
	shoulder_->SetPosition(ConvertPosition(playerPos, shoulderForward));
	//shoulder_->SetRotation(rotateX_, rotateY_, 0.0f);
	shoulder_->Draw();
}

DirectX::XMFLOAT3 MSShoulderSide::ConvertPosition(DirectX::SimpleMath::Vector3 playerPos, DirectX::SimpleMath::Vector3 shoulderForward) {
	DirectX::XMFLOAT3 position = playerPos + shoulderForward * DIST_FROM_CENTER_TO_SHOULDER_JEGAN;
	return position;
}