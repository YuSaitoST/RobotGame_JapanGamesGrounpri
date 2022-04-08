#include "PlayerBase.h"

#include<stdio.h>
#include<cstdlib>


PlayerBase::PlayerBase() {
	player_model = nullptr;
	player_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	speed = 0.0f;

	//�W�����v �֐�
	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;

}

void PlayerBase::Initialize() {
	player_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	jump_flag = false;
}

void PlayerBase::LoadModel() {
	player_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player\\SwordManEX\\armor_red2_0210b.X");
}

void PlayerBase::LoadEffect() {

}

void LoadCsv() {
	FILE* file;  // csv�����ϐ�
 /*
	_wfopen_s�Ńt�@�C�����J���AL"r"�͊J�����̎w��(����͓ǂݍ���)
	�ϐ��ɑ������̂́A�ǂݍ��߂����̃`�F�b�N�̂���
 */

	auto a = _wfopen_s(&file, L"", L"r");
	if (a == 0);// �t�@�C�����J���Ȃ��ꍇ��O�ŗ��Ƃ�
 // * assert���ƃf�o�b�O���ɂ����@�\���Ȃ����߁Aabort()��retun exception�̕����悫

 // PL�⑼��PG�ɂȂ�̒l���������镔����ǂݍ���(���[�J���ϐ��ɓ���邾��)
	char dummy[512];
	fgets(dummy, 500, file);

	/*
   �{���̒l����A%i��int�^�A%f��float�^�A%s��string�^
   ���̌�ɁA.h�Œ�`�����ϐ��̎Q�Ƃ�n��
	*/
	//fscanf_s(file, "%i,%f,%s", &interger, &floatnum, &str);

	// �t�@�C�������
	fclose(file);

}

void PlayerBase::Move_Front(const float deltaTime) {
	player_pos.z -= speed * deltaTime;
}

void PlayerBase::Move_Back(const float deltaTime) {
	player_pos.z += speed * deltaTime;
}

void PlayerBase::Move_Right(const float deltaTime) {
	player_pos.x += speed * deltaTime;
}

void PlayerBase::Move_Left(const float deltaTime) {
	player_pos.x -= speed * deltaTime;
}

void PlayerBase::Dush(const float deltaTime) {
	if (dush_flag) {
		dush_->Update(deltaTime);
	}
}


void PlayerBase::Jump(const float deltaTime) {
	if (jump_flag) {

		jump_time += deltaTime;
		auto pos = player_model->GetPosition();
		
		pos.y = jump_start_v_ + V0 * jump_time - 0.5f * gravity_ * jump_time * jump_time;
		player_model->SetPosition(pos);

		if (player_model->GetPosition().y <= 0.65f) {
			jump_flag = false;			
		}
	}

}


void PlayerBase::Render() {
	player_model->Draw();
}