#include "Fields.h"

void Fields::LoadAssets() {
	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models_Field\\field.X");
	model_->SetPosition(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
}

void Fields::Render() {
	model_->Draw();
}