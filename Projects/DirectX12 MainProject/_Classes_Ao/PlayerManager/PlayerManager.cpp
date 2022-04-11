#include "PlayerManager.h"

void PlayerManager::Initialize() {
	p_base_.Initialize();
	
}

void PlayerManager::LoadModel() {
	p_base_.LoadModel();
}

void PlayerManager::Update(const float deltaTime) {

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
	if (!p_base_.GetJump()) {
		if (Press.JumpEventKey()) {
			p_base_.Jump(deltaTime);
		}
	}
	
}

void PlayerManager::Render() {
	p_base_.Render();
}

void PlayerManager::_2D() {
	p_base_.Render();
}