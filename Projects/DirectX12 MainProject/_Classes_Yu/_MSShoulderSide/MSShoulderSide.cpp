#include "MSShoulderSide.h"

void MSShoulderSide::LoadAsset(std::wstring fileName) {
	shoulder_ = DX9::Model::CreateFromFile(DXTK->Device9, fileName.c_str());
}

void MSShoulderSide::Render() {
	shoulder_->SetPosition(position_);
	shoulder_->SetRotation(rotateX_, rotateY_, 0.0f);
	shoulder_->Draw();
}

void MSShoulderSide::ConvertPosition(Vector3 playerPos, Vector3 shoulderForward) {
	position_ = playerPos + shoulderForward * DIST_FROM_CENTER_TO_SHOULDER;
}