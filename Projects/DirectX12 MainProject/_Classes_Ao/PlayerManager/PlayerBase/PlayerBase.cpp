#include "PlayerBase.h"

#include<stdio.h>
#include<cstdlib>

#include "_Classes_Yu/_FIelds/ConstiateParam.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "_Classes_Yu/_InputClasses/UseKeyCheck.h"


PlayerBase::PlayerBase() {
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::PLAYER, SimpleMath::Vector3::Zero, 1.0f);

	player_model = nullptr;
	pos_ = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	speed = 0.0f;

	//�_�b�V�� �֐�
	Boost_zero = 0;//�I�[�o�[�q�[�g�̏����l
	Boost_max  = 0; //�I�[�o�[�q�[�g�̍ő�l
	overheart_flag = false; //�I�[�o�[�q�[�g�̃t���O


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
	speed = 60.0f;

	//�_�b�V�� �֐�
	Boost_zero = 0;     //�I�[�o�[�q�[�g�̏����l
	Boost_max  = 100;   //�I�[�o�[�q�[�g�̍ő�l
	overheart_flag = false; //�I�[�o�[�q�[�g�̃t���O


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
	frist_reception_max = 1.0f;  //��t���ԍő�l
	frist_check_flag = false;    //���ɍU���Ɉڂ�

    //�񌂖�
	second_reception_time = 0.0f; //��t���ԏ����l
	second_reception_max = 1.0f;  //��t���ԍő�l
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
	debag_font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	time_font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
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
	
	if (Press.MovePlayerStateUp() || Press.MovePlayerStateDown() || Press.MovePlayerStateLeft() || Press.MovePlayerStateRight()) {
		SetAnimation(player_model, RUN);
	}
}


void PlayerBase::Dush(const float deltaTime) {
	if (!overheart_flag) {
		//�_�b�V���������Ă���Ԃ����X�s�[�hUP
		if (Press.DushStateKey()) {
			speed = 120.0f;	
			Boost_max -= 1 * deltaTime;
		}
		else {
			//��������u�[�X�g�Q�[�W��
			speed = 60.0f;
			Boost_max += 2;
		}

		if (Boost_max == Boost_zero) {
			speed = 60.0f;
			overheart_flag = true;
		}
	}

	//�I�[�o�[�q�[�g��
	if (overheart_flag)
		overheart_time += deltaTime;
	if (overheart_time >= overheart_max) {
		overheart_flag = false;
		overheart_time = 0.0f;
	}


	Boost_max = std::clamp(Boost_max, 0, 100);
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
		
		second_reception_time += deltaTime;

		//��t���ԓ��ɍU���{�^������������t���O���������̍U���Ɉڂ�
		if (second_reception_time <= second_reception_max&&
			Press.AtackEventKey()) {
			second_check_flag = true;
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

	if (burst_state_mode == BURST_STATE::NOT_BURST) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Blue,
			L"0"
		);
	}
	else if (burst_state_mode == BURST_STATE::FIRST) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Blue,
			L"1"
		);

		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Blue,
			L"��t���� %f", frist_reception_time
		);
	}
	else if (burst_state_mode == BURST_STATE::SECOND) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Blue,
			L"2"
		);

		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Blue,
			L"��t���� %f", second_reception_time
		);

	}
	else if (burst_state_mode == BURST_STATE::THIRD) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Blue,
			L"3"
		);


		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Blue,
			L"��t���� %f", third_reception_time
		);

	}

	DX9::SpriteBatch->DrawString(
		debag_font.Get(),
		SimpleMath::Vector2(0.0f, 100.0f),
		DX9::Colors::Green,
		L"�u�[�X�g�Q�[�W %d", Boost_max
	);

	if (overheart_flag) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 130.0f),
			DX9::Colors::Blue,
			L"�I�[�o�[�q�[�g ON"
		);

		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 160.0f),
			DX9::Colors::Blue,
			L"�I�[�o�[�q�[�g�����܂Ŏc�� %f �b",(int)overheart_time
		);

	}
}


//�w�肳�ꂽ���[�V������TRUE,����ȊO��FALSE
void PlayerBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}
