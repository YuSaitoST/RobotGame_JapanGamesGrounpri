#include "PlayerManager.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"

void PlayerManager::Initialize() {
	camera->SetView(SimpleMath::Vector3(0, 0, 0), SimpleMath::Vector3(0, 0, 0));
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
	DXTK->Direct3D9->SetCamera(camera);

	p_base_.Initialize();
	// プレイヤーのposのポインタ
	PlayerInfo.SetMenber(p_base_.GetPlayer_Pos());
	
}

void PlayerManager::LoadModel() {
	p_base_.LoadModel();
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
	//前
	if (Press.MovePlayerStateUp()) {
		p_base_.Move_Front(deltaTime);
	}

	//後ろ
	if (Press.MovePlayerStateDown()) {
		p_base_.Move_Back(deltaTime);
	}

	//右
	if (Press.MovePlayerStateRight()) {
		p_base_.Move_Right(deltaTime);
	}

	//左
	if (Press.MovePlayerStateLeft()) {
		p_base_.Move_Left(deltaTime);
	}

	//ダッシュ
	if (Press.DushStateKey()) {
		p_base_.Dush(deltaTime);
	}
	
	//攻撃(近接)

	
	//攻撃(射撃)
	

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
	p_base_.Render();
}