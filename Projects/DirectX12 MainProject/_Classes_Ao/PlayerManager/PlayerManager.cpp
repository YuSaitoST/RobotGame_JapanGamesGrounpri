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

	//�J�����̉�]
	camera_.Update(deltaTime, p_base_.GetPos());

	p_base_.Update(deltaTime);

	//�ړ�
	p_base_.Move(deltaTime,camera_.GetCamera());


	//�J�����̒Ǐ]
	camera_.Setting(p_base_.GetPos());

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
	//DXTK->Direct3D9->SetCamera(camera);

	camera_.Render();
	p_base_.Render();
}

void PlayerManager::_2D() {
	p_base_.UIRender();
}