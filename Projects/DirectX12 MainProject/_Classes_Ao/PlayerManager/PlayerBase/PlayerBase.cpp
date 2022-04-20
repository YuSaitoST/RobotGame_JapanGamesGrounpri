#include "PlayerBase.h"

#include<stdio.h>
#include<cstdlib>

#include "_Classes_Yu/_FIelds/ConstiateParam.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "_Classes_Yu/_InputClasses/UseKeyCheck.h"


PlayerBase::PlayerBase() {
	SetBaseMember(OBJ_TYPE::PLAYER, SimpleMath::Vector3::Zero, 1.0f);

	player_model = nullptr;
	pos_ = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	speed = 0.0f;

	//�W�����v �֐�
	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;
	//1/2
	half = 0.0f;
	//�d�͉����x
	gravity_ = 0.0f;
	//����
	V0 = 0.0f;


	//�ߐڍU�� �R���{
	burst_state_mode = BURST_STATE::NOT_BURST;
	//�ꌂ��
	frist_reception_time = 0.0f; //��t���ԏ����l
	frist_reception_max = 0.0f;  //��t���ԍő�l
	frist_check_flag = false;     //���ɍU���Ɉڂ�

   //�񌂖�
	second_reception_time = 0.0f; //��t���ԏ����l
	second_reception_max = 0.0f;   //��t���ԍő�l
	second_check_flag = false;      //���ɍU���Ɉڂ�


   //�O����
	third_reception_time = 0.0f; //��t���ԏ����l
	third_reception_max = 0.0f;  //��t���ԍő�l
	third_check_flag = false;     //�Ō�I���܂ōU���s��



}

void PlayerBase::Initialize(const int id) {

	pos_ = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	jump_flag = false;
	speed = 60.0f;

	//�W�����v �֐�
	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;
	//1/2
	half = 0.5f;
	//�d�͉����x
	gravity_ = 50.0f;
	//����
	V0 = 40.0f;

	//�ߐڍU�� �R���{
	burst_state_mode = BURST_STATE::NOT_BURST;

	//�ꌂ��
	frist_reception_time = 0.0f; //��t���ԏ����l
	frist_reception_max = 3.0f;  //��t���ԍő�l
	frist_check_flag = false;    //���ɍU���Ɉڂ�

    //�񌂖�
	second_reception_time = 0.0f; //��t���ԏ����l
	second_reception_max = 3.0f;  //��t���ԍő�l
	second_check_flag = false;    //���ɍU���Ɉڂ�


    //�O����
	third_reception_time = 0.0f; //��t���ԏ����l
	third_reception_max = 1.0f;  //��t���ԍő�l
	third_check_flag = false;    //�Ō�I���܂ōU���s��


	PlayerInfo.SetMenber(&pos_, &attackState_);

}


void PlayerBase::LoadAssets(std::wstring file_name) {
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

	auto a = _wfopen_s(&file, L"PlayerParams.csv", L"r");
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

void PlayerBase::Setting(const float deltaTime) {
	player_model->SetRotation(0.0f, XMConvertToRadians(180.0f), 0.0f);
	pos_ = player_model->GetPosition();
	
	//�ړ�����
	pos_ = SimpleMath::Vector3(
		pos_.x = std::min(std::max(0.0f, pos_.x), FLParams.LENGHT_OF_A_SIDE),
		pos_.y = std::min(std::max(0.0f, pos_.y), 10000.0f),
		pos_.z = std::min(std::max(0.0f, pos_.z), FLParams.LENGHT_OF_A_SIDE)
	);

	player_model->AdvanceTime(deltaTime);
	player_model->SetPosition(pos_);
}

void PlayerBase::Update(const float deltaTime) {
	SetAnimation(player_model, STAND);

	
	UpdateToMorton();
}

void PlayerBase::Move(const float deltaTime) {
	forward_ = Vector3(-Press.DirectionKey().x, 0.0f, Press.DirectionKey().y);
	Vector3 amountMove = forward_ * speed * deltaTime;
	player_model->Move(amountMove);
}


void PlayerBase::Dush(const float deltaTime) {
	if (dush_flag) {
		
	}
}

//�ߐڍU��
void PlayerBase::Attack(const float deltaTime) {
	attackState_ = AttackState::Adjacent;
	switch (burst_state_mode)
	{
	case BURST_STATE::NOT_BURST:
		if (Press.AtackEventKey())
			burst_state_mode = BURST_STATE::FIRST;
		break;
	case BURST_STATE::FIRST:
		SetAnimation(player_model, ACT1);
		frist_reception_time += deltaTime;

		//��t���ԓ��ɍU���{�^������������t���O���������̍U���Ɉڂ�
		if (frist_reception_time <= frist_reception_max && 
			Press.AtackEventKey()) {
			frist_check_flag = true;
		}

		// ��t���Ԃɉ�����Ă����玟�̍U����
		if (frist_reception_time >= frist_reception_max && frist_check_flag) {
			frist_reception_time = 0.0f;
			frist_check_flag = false;
			burst_state_mode = BURST_STATE::SECOND;

		}
		//��t���Ԃɉ�����Ă��Ȃ������烊�Z�b�g
		else if (frist_reception_time >= frist_reception_max && !frist_check_flag) {
			frist_reception_time = 0.0f;
			frist_check_flag = false;
			burst_state_mode = BURST_STATE::NOT_BURST;
		}

		break;
	case BURST_STATE::SECOND:
		SetAnimation(player_model, ACT2);
		second_reception_time += deltaTime;

		if (second_reception_time <= second_reception_max) {

		}

		// ��t���Ԃɉ�����Ă����玟�̍U����
		if (second_reception_time >= second_reception_max && second_check_flag) {
			second_reception_time = 0.0f;
			second_check_flag = false;
			burst_state_mode = BURST_STATE::THIRD;

		}
		//��t���Ԃɉ�����Ă��Ȃ������烊�Z�b�g
		else if (second_reception_time >= second_reception_max && !second_check_flag) {
			second_reception_time = 0.0f;
			second_check_flag = false;
			burst_state_mode = BURST_STATE::NOT_BURST;
		}

		break;
	case BURST_STATE::THIRD:
		SetAnimation(player_model, ACT1);
		third_reception_time += deltaTime;
		//�I���
		if (third_reception_time >= third_reception_max) {
			third_reception_time = 0.0f;
			third_reception_time = false;
			burst_state_mode = BURST_STATE::NOT_BURST;

		}

		break;
	}
}

void PlayerBase::Shot(const float deltaTime) {
	attackState_ = AttackState::Shooting;
}

void PlayerBase::Jump(const float deltaTime) {
	//�W�����v
	if (!jump_flag) {
		if (Press.JumpEventKey()) {
			jump_flag = true;
			jump_time = 0;
			jump_start_v_ = player_model->Position.y;

		}
	}
	if (jump_flag) {

		jump_time += deltaTime;
		auto pos = player_model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time - 0.5f * gravity_ * jump_time * jump_time;
		player_model->SetPosition(pos);


		if (player_model->GetPosition().y <= 0.0f) {
			jump_flag = false;
		}
	}

}

void PlayerBase::Render() {
	player_model->Draw();
}

void PlayerBase::Render(DX9::SKINNEDMODEL& model) {
	player_model->Draw();
}


void PlayerBase::UIRender() {
	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 0.0f),
		DX9::Colors::Red,
		L"���W�@%f %f %f", pos_.x, pos_.y, pos_.z
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
