#include "Fields.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "_Parameter/ConstiateParam.h"

Fields::Fields() {
	skyDome_ = new SkyDome();
	kyotens_ = new KyotenRender();
	watchowers_ = new WatchtowerRender();
	domes_ = new DomeRender();
}

Fields::~Fields() {
	delete domes_;
	delete watchowers_;
	delete kyotens_;
	delete skyDome_;
}

void Fields::LoadAssets() {
	skyDome_->LoadAsset();
	kyotens_->LoadAsset();
	watchowers_->LoadAsset();
	domes_->LoadAsset();

	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models_Field\\field.X");
	//model_->SetPosition(DirectX::SimpleMath::Vector3(FLParams.GetFieldFalfScale(), -0.25f, FLParams.GetFieldFalfScale()));
	 model_->SetPosition(DirectX::SimpleMath::Vector3(HALFSIZE, POS_Y, HALFSIZE));
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
	skyDome_->Render(*PlayerInfo.GetPosition());  // Player‚ÌˆÚ“®§ŒÀ‚É‚æ‚Á‚Ä‚ÍÀ•W“n‚·•K—v‚Í‚È‚¢‚©‚à
	kyotens_->Render();
	watchowers_->Render();
	domes_->Render();

	//DXTK->Device9->SetTexture(1, bump_.Get());
	//DirectX::SimpleMath::Matrix mat = model_->GetWorldTransform();
	//shader_->SetParameter("m_WVP", mat);

	//shader_->Begin();
	//shader_->BeginPass(0);
	//model_->SetPosition(DirectX::XMFLOAT3(HALFSIZE, POS_Y, HALFSIZE));
	model_->Draw();

	//model_->SetPosition(DirectX::XMFLOAT3(HALFSIZE * 2, POS_Y, HALFSIZE));
	//model_->Draw();

	//model_->SetPosition(DirectX::XMFLOAT3(HALFSIZE * 2, POS_Y, HALFSIZE * 2));
	//model_->Draw();

	//model_->SetPosition(DirectX::XMFLOAT3(HALFSIZE, POS_Y, HALFSIZE * 2));
	//model_->Draw();
	//shader_->EndPass();
	//shader_->End();

	//DXTK->Device9->SetTexture(1, nullptr);
}