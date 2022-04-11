#include "PlayerManager.h"

void PlayerManager::Initialize() {
	p_base_.Initialize();
	
}

void PlayerManager::LoadModel() {
	p_base_.LoadModel();
}

void PlayerManager::Update(const float deltaTime) {

	p_base_.Setting();

	//�ړ�
	//�O
	if (Press.MovePlayerStateUp()) {
		p_base_.Move_Front(deltaTime);
	}

	//���
	if (Press.MovePlayerStateDown()) {
		p_base_.Move_Back(deltaTime);
	}

	//�E
	if (Press.MovePlayerStateRight()) {
		p_base_.Move_Right(deltaTime);
	}

	//��
	if (Press.MovePlayerStateLeft()) {
		p_base_.Move_Left(deltaTime);
	}

	//�_�b�V��
	if (Press.DushStateKey()) {
		p_base_.Dush(deltaTime);
	}
	//�U��(�ߐ�)
	
	//�U��(�ˌ�)
	
	//�W�����v
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