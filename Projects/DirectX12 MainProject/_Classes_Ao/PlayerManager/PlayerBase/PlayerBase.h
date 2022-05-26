#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "_Classes_Yu/_CellList/_Object/ObjectBase.h"



using namespace DirectX;

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	virtual ~PlayerBase() {};

	void Initialize(const int id);
	void LoadAssets() {}
	void LoadAssets(std::wstring file_name);

	void LoadCsv();

	void Setting(const float deltaTime);
	void Update(const float deltaTime);

	void Move(const float deltaTime, DX9::CAMERA camera);


	void Attack(const float deltaTime);
	void Shot(const float deltaTime);
	void Dush(const float deltaTime);
	void Jump(const float deltaTime);

	void Render();
	void Render(DX9::MODEL& model);
	void UIRender();
	//�A�j���[�V����
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);


	//DX9::MODEL& GetModel() { return player_model; }
	SimpleMath::Vector3* GetPlayer_Pos() { return &pos_; }
	Vector3 GetPos() { return player_model->GetPosition(); }
	float GetCameraRotate() { return camera_rotate_speed; }

private:
	//DX9::SKINNEDMODEL player_model;
	DX9::MODEL player_model;

	DX9::SPRITEFONT font;
	DX9::SPRITEFONT debag_font;
	DX9::SPRITEFONT time_font;

	float camera_rotate_speed;//�J�����̉�]���x
	float player_spped;//�v���C���[�̃X�s�[�h()
	float normal_speed;//�v���C���[�̒ʏ�̃X�s�[�h
	

	//�_�b�V�� �֐� �n��
	//�u�[�X�g���̕ϐ�
	int   boost_zero;//�u�[�X�g�̏����l
	int   boost_max; //�u�[�X�g�̍ő�l
	float boost_dush;//�u�[�X�g���̑��x
	bool  boost_flag;//�u�[�X�g���Ă��邩�̃t���O

	//�I�[�o�[�q�[�g���̕ϐ�
	bool overheart_flag; //�I�[�o�[�q�[�g�̃t���O
	float overheart_time;//�I�[�o�[�q�[�g���Ă��鎞�� �����l
	float overheart_max; //�I�[�o�[�q�[�g���Ă��鎞�� �ő�l
	float overheart_speed = 5.0f;//�I�[�o�[�q�[�g���̃X�s�[�h

	float PlayerSpeedMode();

	

	//�W�����v �֐�
	bool jump_flag = false;
	float jump_time = 0.0f;
	float jump_start_v_ = 0.0f;
	//1/2
	float half = 0.5f;
	//�d�͉����x
	float gravity_ = 50.0f;
	//����
	float V0 = 40.0f;

	//�ߐڍU�� �R���{
	enum  BURST_STATE
	{
		NOT_BURST,
		FIRST,
		SECOND,
		THIRD
	};
	BURST_STATE burst_state_mode;
	 
	//�ꌂ��
	float frist_reception_time; //��t���ԏ����l
	float frist_reception_max;  //��t���ԍő�l
	bool  frist_check_flag;     //���ɍU���Ɉڂ�

	//�񌂖�
	float second_reception_time; //��t���ԏ����l
	float second_reception_max;   //��t���ԍő�l
	bool  second_check_flag;      //���ɍU���Ɉڂ�

	//�O����
	float third_reception_time; //��t���ԏ����l
	float third_reception_max;  //��t���ԍő�l
	bool  third_check_flag;     //�Ō�I���܂ōU���s��

	//�ˌ�
	int shotdamage;
	
};