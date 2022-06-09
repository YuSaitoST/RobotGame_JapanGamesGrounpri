#include "PlayerManager.h"

#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "_Classes_Yu/_LoadCSV/LoadCSV.h"
#include "_Classes_Ao/_Camera/_Camera.h"

void PlayerManager::Initialize() {
	p_base_.Initialize(0);
	
}

void PlayerManager::LoadModel() {
	p_base_.LoadAssets(L"Player\\j_mein.x");

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);


	_Camera::GetInstance().LoadAssets(p_base_.GetPos());

}

void PlayerManager::Update(const float deltaTime) {

	//�J�����̉�]
	_Camera::GetInstance().Update(deltaTime, p_base_.GetPos());

	p_base_.Update(deltaTime);

	//�ړ�
	p_base_.Move(deltaTime,_Camera::GetInstance().GetCamera());


	//�J�����̒Ǐ]
	_Camera::GetInstance().Setting(p_base_.GetPos());

	//�_�b�V��
	p_base_.Dush(deltaTime);

	//�U��(�ߐ�)
	p_base_.Attack(deltaTime);

	//�U��(�ˌ�)
	p_base_.Shot(deltaTime);

	//�W�����v
	p_base_.Jump(deltaTime);

	p_base_.Setting(deltaTime);


}

void PlayerManager::Render() {
	//�J�����̕`��
	_Camera::GetInstance().Render();

	//�v���C���[���f���̕`��
	p_base_.Render();
}

void PlayerManager::_2D() {
	p_base_.UIRender();
}