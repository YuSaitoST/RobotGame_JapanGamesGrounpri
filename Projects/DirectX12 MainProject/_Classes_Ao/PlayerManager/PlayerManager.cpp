#include "PlayerManager.h"

#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "_Classes_Yu/_LoadCSV/LoadCSV.h"


void PlayerManager::Initialize() {
	p_base_.Initialize(0);
	
}


void PlayerManager::LoadModel() {
	p_base_.LoadAssets(L"Player\\j_mein.x");

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);


	camera_.LoadAssets(p_base_.GetPos());

}

void PlayerManager::Update(const float deltaTime) {

	//カメラの回転
	camera_.Update(deltaTime, p_base_.GetPos());

	p_base_.Update(deltaTime);

	//移動
	p_base_.Move(deltaTime,camera_.GetCamera());


	//カメラの追従
	camera_.Setting(p_base_.GetPos());

	//ダッシュ
	p_base_.Dush(deltaTime);

	//攻撃(近接)
	p_base_.Attack(deltaTime);

	//攻撃(射撃)
	p_base_.Shot(deltaTime);

	//ジャンプ
	p_base_.Jump(deltaTime);

	p_base_.Setting(deltaTime);


}

void PlayerManager::Render() {
	//DXTK->Direct3D9->SetCamera(camera);

	camera_.Render();
	p_base_.Render();
}

void PlayerManager::_2D() {
	p_base_.UIRender();
}