#include "Fields.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "_Classes_Yu/_FIelds/_FieldParamsLoad/FieldParamsLoad.h"

Fields::Fields() {
	FieldParamsLoad::GetInstance().LoadParams();
	skyDome_ = new SkyDome();
}

Fields::~Fields() {
	delete skyDome_;
}

void Fields::LoadAssets() {
	skyDome_->LoadAsset();

	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models_Field\\field.X");
	model_->SetPosition(DirectX::SimpleMath::Vector3(0.0f, -0.25f, 0.0f));
	model_->SetScale(FLParams.SCALE, 0.0f, FLParams.SCALE);

	D3DMATERIAL9 _mate{};
	_mate.Diffuse = DX9::Colors::Value(0.35f, 0.35f, 0.35f, 1.0f);
	_mate.Ambient = DX9::Colors::Value(0.35f, 0.35f, 0.35f, 1.0f);
	model_->SetMaterial(_mate);
}

void Fields::Render() {
	skyDome_->Render(*PlayerInfo.GetPosition());  // Player‚ÌˆÚ“®§ŒÀ‚É‚æ‚Á‚Ä‚ÍÀ•W“n‚·•K—v‚Í‚È‚¢‚©‚à
	model_->Draw();
}