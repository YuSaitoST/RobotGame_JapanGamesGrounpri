#include "PlayerManager.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"

void PlayerManager::Initialize() {
	camera->SetView(SimpleMath::Vector3(0, 0, 0), SimpleMath::Vector3(0, 0, 0));
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
	DXTK->Direct3D9->SetCamera(camera);

	p_base_.Initialize(0);
	// プレイヤーのposのポインタ
	
}

void PlayerManager::LoadModel() {
	p_base_.LoadAssets(L"Player\\SwordManEX\\armor_red2_0210b.X");
}

void PlayerManager::Update(const float deltaTime) {
	p_base_.Update(deltaTime);
	camera->SetPosition(
		p_base_.GetModel()->GetPosition().x + 2.0f,
		p_base_.GetModel()->GetPosition().y + 5.5f,
		p_base_.GetModel()->GetPosition().z - 6.0f
	);
	camera->SetRotation(XMConvertToRadians(20.0f), 0.0f, 0.0f);


	//移動
	p_base_.Move(deltaTime);

	//ダッシュ
	if (Press.DushStateKey()) {
		p_base_.Dush(deltaTime);
	}


	//攻撃(近接)
	//p_base_.Attack(deltaTime);
	if (Press.AtackEventKey()) {
		p_base_.Attack(deltaTime);
	}

	if (p_base_.BurstState() == PlayerBase::BURST_STATE::FIRST &&
		p_base_.GetFristReceptionTime() <= 1.0f) {
		if (Press.AtackEventKey()) {
			p_base_.FristCheckFlag();
		}
	}
	if (p_base_.BurstState() == PlayerBase::BURST_STATE::SECOND &&
		p_base_.GetSecondReceptionTime() <= 1.0f) {
		if (Press.AtackEventKey()) {
			p_base_.SecondCheckFlag();
		}
	}


	//攻撃(射撃)
	if (Press.ShotEventKey()) {
		p_base_.Shot(deltaTime);
	}

	//ジャンプ
	p_base_.Jump(deltaTime);


	p_base_.Setting(deltaTime);
}

void PlayerManager::Render() {
	DXTK->Direct3D9->SetCamera(camera);

	p_base_.Render();
}

void PlayerManager::_2D() {
	p_base_.UIRender();
}