#include "PlayerBase.h"

#include<stdio.h>
#include<cstdlib>

#include "_Classes_Yu/_FIelds/ConstiateParam.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "_Classes_Yu/_InputClasses/UseKeyCheck.h"
#include "_Classes_Yu/_CellList/ObjectManager.h"
#include "_Classes_Yu/_FieldOutCheck/FieldOutCheck.h"
#include "_Classes_Yu/_MeleeWeapon/MeleeWeapon.h"

#include "_Classes_Ao/PlayerManager/PlayerManager.h"


PlayerBase::PlayerBase() {
	LoadCsv();
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::PLAYER, SimpleMath::Vector3::Zero, 1.0f);

	player_model = nullptr;
	pos_ = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	speed = 0.0f;

	//�_�b�V�� �֐�
	boost_zero = 0;//�I�[�o�[�q�[�g�̏����l
	boost_max  = 0; //�I�[�o�[�q�[�g�̍ő�l
	//�I�[�o�[�q�[�g���̕ϐ�
	overheart_flag = false; //�I�[�o�[�q�[�g�̃t���O
	overheart_time = 0.0f;//�I�[�o�[�q�[�g���Ă��鎞�� �����l
	overheart_max = 0.0f; //�I�[�o�[�q�[�g���Ă��鎞�� �ő�l


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
	
	pos_ = SimpleMath::Vector3(pos_.x, 0.0f, pos_.z);



	//�_�b�V�� �֐�
	boost_zero = 0;     //�I�[�o�[�q�[�g�̏����l
	boost_max  = 100;   //�I�[�o�[�q�[�g�̍ő�l
	//�I�[�o�[�q�[�g���̕ϐ�
	overheart_flag=false; //�I�[�o�[�q�[�g�̃t���O
	overheart_time=0.0f;//�I�[�o�[�q�[�g���Ă��鎞�� �����l
	overheart_max=3.0f; //�I�[�o�[�q�[�g���Ă��鎞�� �ő�l


	//�W�����v �֐�
	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;
	//1/2
	half = 0.5f;
	//�d�͉����x
	gravity_ = 3.14f;
	//����
	V0 = 1.0f;

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
	//player_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player\\j_mein.x");
	player_model = DX9::Model::CreateFromFile(DXTK->Device9,L"Player\\j_mein.x");

	player_model->SetRotation(0.0f, XMConvertToRadians(180.0f), 0.0f);
	player_model->SetPosition(pos_);
	
	
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	debag_font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	time_font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}
void PlayerBase::LoadEffect() {

}

void PlayerBase::LoadCsv() {
	FILE* file;  // csv�����ϐ�
 /*
	_wfopen_s�Ńt�@�C�����J���AL"r"�͊J�����̎w��(����͓ǂݍ���)
	�ϐ��ɑ������̂́A�ǂݍ��߂����̃`�F�b�N�̂���
 */

	auto a = _wfopen_s(&file, L"_Parameters\\PlayerParams.csv", L"r");
	if (a != 0)// �t�@�C�����J���Ȃ��ꍇ��O�ŗ��Ƃ�
		abort();
 // * assert���ƃf�o�b�O���ɂ����@�\���Ȃ����߁Aabort()��retun exception�̕����悫

 // PL�⑼��PG�ɂȂ�̒l���������镔����ǂݍ���(���[�J���ϐ��ɓ���邾��)
	char dummy[512];
	fgets(dummy, 500, file);

	/*
   �{���̒l����A%i��int�^�A%f��float�^�A%s��string�^
   ���̌�ɁA.h�Œ�`�����ϐ��̎Q�Ƃ�n��
	*/
	fscanf_s(file, "%f,%f,%f,%f,%i", &player_spped, &boost_dush, &pos_.x, &pos_.z, &shotdamage);

	// �t�@�C�������
	fclose(file);

}

void PlayerBase::Update(const float deltaTime) {
	pos_ = player_model->GetPosition();

	Field::ClampPosition(pos_);
	player_model->SetPosition(pos_);

	UpdateToMorton();
}

void PlayerBase::Setting(const float deltaTime) {



	//�ړ�����	
	Field::IsOut(pos_);

}

void PlayerBase::Move(const float deltaTime, DX9::CAMERA camera) {

	camera_forward = camera.GetForwardVector();
	
	
	forward_ = Vector3(-Press.DirectionKey().x, 0.0f, Press.DirectionKey().y);
	//camera_forward = Vector3(-Press.DirectionKey().x, 0.0f, Press.DirectionKey().y);
	Vector3 amountMove = forward_ * speed * deltaTime;
	player_model->Move(amountMove);

}


void PlayerBase::Dush(const float deltaTime) {
	if (!overheart_flag) {
		//�_�b�V���������Ă���Ԃ����X�s�[�hUP
		if (Press.DushStateKey()) {
			speed = boost_dush;
			boost_max -= 1 * deltaTime;
		}
		else {
			//��������u�[�X�g�Q�[�W��
			speed = player_spped;
			boost_max += 2;
		}
		if (boost_max == boost_zero) {
			speed = player_spped;
			overheart_flag = true;
		}
	}

	//�I�[�o�[�q�[�g��
	if (overheart_flag) {
		overheart_time += deltaTime;
		if (overheart_time >= overheart_max) {
			overheart_flag = false;
			boost_max = 100;
			overheart_time = 0.0f;
		}
	}

	boost_max = std::clamp(boost_max, 0, 100);
}

//�ߐڍU��
void PlayerBase::Attack(const float deltaTime) {
	
	switch (burst_state_mode)
	{
	case BURST_STATE::NOT_BURST:
		if (Press.AtackEventKey()) {
			burst_state_mode = BURST_STATE::FIRST;
			attackState_ = AttackState::Adjacent;
		}
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
			attackState_ = AttackState::None_Attack;
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
			attackState_ = AttackState::None_Attack;
		}

		break;
	case BURST_STATE::THIRD:
		
		third_reception_time += deltaTime;
		//�I���
		if (third_reception_time >= third_reception_max) {
			third_reception_time = 0.0f;
			third_reception_time = false;
			burst_state_mode = BURST_STATE::NOT_BURST;
			attackState_ = AttackState::None_Attack;
		}
		break;
	}

}

void PlayerBase::Shot(const float deltaTime) {
	if (Press.ShotEventKey()) {
		attackState_ = AttackState::Shooting;
		Vector3 flont = player_model->GetRotation();
		ObjectManager::SetShooting(id_my_, shotdamage, pos_, -flont, rotateY_);
		attackState_ = AttackState::None_Attack;
	}
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
			player_model->SetPosition(pos.x, 0.0f, pos.z);
			jump_flag = false;
		}
	}

}

void PlayerBase::Render() {
	player_model->Draw();
}

void PlayerBase::Render(DX9::MODEL& model) {
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
			DX9::Colors::Red,
			L"�A�� 0"
		);
	}
	else if (burst_state_mode == BURST_STATE::FIRST) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Red,
			L"�A�� 1�A����"
		);

		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Red,
			L"��t���� %f", frist_reception_time
		);
	}
	else if (burst_state_mode == BURST_STATE::SECOND) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Red,
			L"�A�� 2�A����"
		);

		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Red,
			L"��t���� %f", second_reception_time
		);

	}
	else if (burst_state_mode == BURST_STATE::THIRD) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Red,
			L"�A�� 3�A����"
		);


		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Red,
			L"��t���� %f", third_reception_time
		);

	}

	DX9::SpriteBatch->DrawString(
		debag_font.Get(),
		SimpleMath::Vector2(0.0f, 100.0f),
		DX9::Colors::Green,
		L"�u�[�X�g�Q�[�W %d", boost_max
	);

	if (overheart_flag) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 130.0f),
			DX9::Colors::Red,
			L"�I�[�o�[�q�[�g ON"
		);

		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 160.0f),
			DX9::Colors::Red,
			L"�I�[�o�[�q�[�g�����܂Ŏc�� %f �b",overheart_time
		);
	}
	else
	{
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 130.0f),
			DX9::Colors::Red,
			L"�I�[�o�[�q�[�g OFF"
		);
	}

	//DX9::SpriteBatch->DrawString(
	//	debag_font.Get(),
	//	SimpleMath::Vector2(0.0f, 200.0f),
	//	DX9::Colors::Red,
	//	L"Forward X %f Y %f Z %f", forward_.x,forward_.y,forward_.z
	//);

	DX9::SpriteBatch->DrawString(
		debag_font.Get(),
		SimpleMath::Vector2(0.0f, 200.0f),
		DX9::Colors::Red,
		L"Camera_Forward X %f Y %f Z %f", camera_forward.x, camera_forward.y, camera_forward.z
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