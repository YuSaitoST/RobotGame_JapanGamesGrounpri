#include "Fields.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "ConstiateParam.h"

Fields::Fields() {
	skyDome_ = new SkyDome();
}

Fields::~Fields() {
	delete skyDome_;
}

void Fields::LoadAssets() {
	skyDome_->LoadAsset();

	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models_Field\\field.X");
	//model_->SetPosition(DirectX::SimpleMath::Vector3(FLParams.GetFieldFalfScale(), -0.25f, FLParams.GetFieldFalfScale()));
	 model_->SetPosition(DirectX::SimpleMath::Vector3(4, -0.25f, 4));
	//model_->SetScale(FLParams.GetNumber().SCALE, 0.0f, FLParams.GetNumber().SCALE);
	//const float size = 0.2032f * 50.0f * 10;
	//model_->SetScale(size, 1.0f, size);
	model_->SetScale(1.0f, 1.0f, 1.0f);

	D3DMATERIAL9 _mate{};
	_mate.Diffuse = DX9::Colors::Value(0.35f, 0.35f, 0.35f, 1.0f);
	_mate.Ambient = DX9::Colors::Value(0.35f, 0.35f, 0.35f, 1.0f);
	model_->SetMaterial(_mate);

	//bump_ = DX9::Texture::CreateFromFile(DXTK->Device9, L"");
	//shader_ = DX9::Shader::CreateFromFile(DXTK->Device9, L"");
}

void Fields::Render() {
	skyDome_->Render(*PlayerInfo.GetPosition());  // Playerの移動制限によっては座標渡す必要はないかも

	//DXTK->Device9->SetTexture(1, bump_.Get());
	//DirectX::SimpleMath::Matrix mat = model_->GetWorldTransform();
	//shader_->SetParameter("m_WVP", mat);

	//shader_->Begin();
	//shader_->BeginPass(0);
	model_->Draw();
	//shader_->EndPass();
	//shader_->End();

	//DXTK->Device9->SetTexture(1, nullptr);
}