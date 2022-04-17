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
	speed = 60.0f;

	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;

}


void PlayerBase::LoadModel() {
	player_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player\\SwordManEX\\armor_red2_0210b.X");
	player_model->SetScale(0.1f);
	
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

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

void PlayerBase::Setting() {
	player_model->SetRotation(0.0f, XMConvertToRadians(180.0f), 0.0f);
	player_pos = player_model->GetPosition();

	//�ړ�����
	player_pos.x = std::min(std::max(player_pos.x, 0.0f),  200.0f);
	player_pos.y = std::min(std::max(player_pos.y, 0.0f), 10000.0f);
	player_pos.z = std::min(std::max(player_pos.z, 0.0f),  200.0f);


}

void PlayerBase::Move_Front(const float deltaTime) {
	player_model->Move(0.0f, 0.0f, -speed * deltaTime);
}

void PlayerBase::Move_Back(const float deltaTime) {
	player_model->Move(0.0f, 0.0f, speed * deltaTime);
}

void PlayerBase::Move_Right(const float deltaTime) {
	player_model->Move(-speed * deltaTime, 0.0f, 0.0f);
}

void PlayerBase::Move_Left(const float deltaTime) {
	player_model->Move(speed * deltaTime, 0.0f, 0.0f);
}

void PlayerBase::Dush(const float deltaTime) {
	if (dush_flag) {
		
	}
}

//void PlayerBase::Attack(const float deltaTime) {
//	switch (burst_state_mode)
//	{
//	case BURST_STATE::NOT_BURST:
//		burst_state_mode = BURST_STATE::FIRST;
//		break;
//	case BURST_STATE::FIRST:
//		SetAnimation(player_model, ACT1);
//		first_burst_start += deltaTime;
//
//		attack_flag = true;
//
//		if (first_burst_start >= 0.15f && DXTK->KeyEvent->pressed.S) {
//			first_burst_flag = true;
//		}
//		if (first_burst_start >= first_burst_end && first_burst_flag) {
//			burst_state_mode = BURST_STATE::SECOND;
//			model->SetTrackPosition(ACT1, 0.0);
//			first_burst_start = 0.0f;
//			first_burst_flag = false;
//		}
//		else if (first_burst_start >= first_burst_end) {
//			burst_state_mode = BURST_STATE::NOT_BURST;
//			model->SetTrackPosition(ACT1, 0.0);
//			first_burst_start = 0.0f;
//			first_burst_flag = false;
//		}
//
//		break;
//	case BURST_STATE::SECOND:
//		SetAnimation(model, ACT2);
//		second_burst_start += deltaTime;
//
//		attack_flag = true;
//
//
//		if (second_burst_start >= 0.15f && DXTK->KeyEvent->pressed.S)
//			second_burst_flag = true;
//
//		if (second_burst_start >= second_burst_end && second_burst_flag) {
//			burst_state_mode = BURST_STATE::THIRD;
//			model->SetTrackPosition(ACT2, 0.0);
//
//			second_burst_start = 0.0f;
//			second_burst_flag = false;
//		}
//		else if (second_burst_start >= second_burst_end) {
//			burst_state_mode = BURST_STATE::NOT_BURST;
//			model->SetTrackPosition(ACT2, 0.0);
//			second_burst_start = 0.0f;
//			second_burst_flag = false;
//		}
//
//		break;
//	case BURST_STATE::THIRD:
//		SetAnimation(model, ACT3);
//		third_burst_start += deltaTime;
//
//		attack_flag = true;
//
//
//		if (third_burst_start >= 0.15f && DXTK->KeyEvent->pressed.S)
//			third_burst_flag = true;
//
//		if (third_burst_start >= third_burst_end) {
//			burst_state_mode = BURST_STATE::NOT_BURST;
//			model->SetTrackPosition(ACT3, 0.0);
//			third_burst_start = 0.0f;
//			third_burst_flag = false;
//		}
//
//		break;
//	}
//
//}


void PlayerBase::Jump(const float deltaTime) {
	if (!jump_flag) {
		jump_flag = true;
		jump_time = 0.0f;
		jump_start_v_ = player_model->Position.y;
	}

	if (jump_flag) {
		jump_time += deltaTime;
		auto pos = player_model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time - half * gravity_ * jump_time * jump_time;
		player_model->SetPosition(pos);
		
		//�W�����v�̏I������
		if (V0 * jump_time < gravity_ * jump_time * jump_time) {
			jump_flag = false;
			auto pl = 0;
		}
	}

}


void PlayerBase::Render() {
	player_model->Draw();
}
void PlayerBase::_2D() {
	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 0.0f),
		DX9::Colors::Red,
		L"���W�@%f %f %f",player_pos.x, player_pos.y, player_pos.z
	);
}

//�w�肳�ꂽ���[�V������TRUE,����ȊO��FALSE
void PlayerBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}
