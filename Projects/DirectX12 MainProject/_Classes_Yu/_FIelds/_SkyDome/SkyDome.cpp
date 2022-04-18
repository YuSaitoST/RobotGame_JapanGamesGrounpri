#include "SkyDome.h"

void SkyDome::LoadAsset() {
	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models_SkyDome\\Dome.x");
	model_->SetScale(3.5f);
}

void SkyDome::Render(const DirectX::SimpleMath::Vector3 pos) {
	model_->SetPosition(pos.x, 0.0f, pos.z);
	model_->Draw();
}