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
	camera->SetPosition(
		p_base_.GetModel()->GetPosition().x + 2.0f,
		p_base_.GetModel()->GetPosition().y + 5.5f,
		p_base_.GetModel()->GetPosition().z - 6.0f
	);
	camera->SetRotation(XMConvertToRadians(20.0f), 0.0f, 0.0f);

	p_base_.Setting();

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
	if (!jump_flag) {
		if (Press.JumpEventKey()) {
			jump_flag = true;
			jump_time = 0;
			jump_start_v_ = p_base_.GetModel()->GetPosition().y;

		}
	}


	if (jump_flag) {

		jump_time += deltaTime;
		auto pos = p_base_.GetModel()->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time - 0.5f * gravity_ * jump_time * jump_time;
		p_base_.GetModel()->SetPosition(pos);

		if (p_base_.GetModel()->GetPosition().y <= 0.01f) {
			jump_flag = false;
			}
	}

	
}

void PlayerManager::Render() {
	DXTK->Direct3D9->SetCamera(camera);

	p_base_.Render();
}

void PlayerManager::_2D() {
	p_base_.UIRender();
}