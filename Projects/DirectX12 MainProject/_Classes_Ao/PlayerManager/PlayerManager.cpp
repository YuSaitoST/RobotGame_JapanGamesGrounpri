#include "PlayerManager.h"

void PlayerManager::Initialize() {
	camera->SetView(SimpleMath::Vector3(0, 0, 0), SimpleMath::Vector3(0, 0, 0));
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
	DXTK->Direct3D9->SetCamera(camera);

	p_base_.Initialize();
	
}

void PlayerManager::LoadModel() {
	p_base_.LoadModel();
}

void PlayerManager::Update(const float deltaTime) {
	camera->SetPosition(
		p_base_.GetModel()->GetPosition().x + 2.5f,
		p_base_.GetModel()->GetPosition().y + 5.0f,
		p_base_.GetModel()->GetPosition().z - 10.0f
	);
	camera->SetRotation(XMConvertToRadians(10.0f), 0.0f, 0.0f);

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
	DXTK->Direct3D9->SetCamera(camera);

	p_base_.Render();
}

void PlayerManager::_2D() {
	p_base_.Render();
}