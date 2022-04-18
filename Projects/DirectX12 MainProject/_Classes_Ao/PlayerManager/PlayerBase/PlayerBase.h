#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "_Classes_Ao/PlayerManager/PlayerBase/Dush/Dush.h"
#include "_Classes_Yu/_CellList/_Object/ObjectBase.h"

using namespace DirectX;

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	virtual ~PlayerBase() {};

	void Initialize(const int id);

	void LoadAssets(std::wstring file_name);
	void LoadEffect();

	void Setting();
	void Update(const float deltaTime);

	void Move_Front(const float deltaTime);
	void Move_Back(const float deltaTime);
	void Move_Right(const float deltaTime);
	void Move_Left(const float deltaTime);


	void Attack(const float deltaTime);
	void Shot(const float deltaTime);
	void Dush(const float deltaTime);
	void Jump(const float deltaTime);

	void Render();
	void Render(DX9::SKINNEDMODEL& model);
	void UIRender();
	//�A�j���[�V����
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);


	DX9::SKINNEDMODEL& GetModel() { return player_model; }
	SimpleMath::Vector3* GetPlayer_Pos() { return &pos_; }

	//�U��
	enum AtackMode
	{
		MeleeAttack, //�ߐڍU��
		ShotAttack   //�ˌ�
	};
	AtackMode attack_mode_state;
	AtackMode AtackState() { return attack_mode_state; }

	//�ߐڍU�� �R���{
    //�O�A��
	enum  BURST_STATE
	{
		NOT_BURST,
		FIRST,
		SECOND,
		THIRD
	};
	BURST_STATE burst_state_mode;
	BURST_STATE BurstState() { return burst_state_mode; }

	//�R���{�@��t���� �֐�
	float GetFristReceptionTime() { return frist_reception_time; }
	float GetSecondReceptionTime() { return second_reception_time; }
	float GetThirdReceptionTime() { return third_reception_time; }

	//�R���{�@���́@�֐�
	bool FristCheckFlag() { return frist_check_flag; }     //���ɍU���Ɉڂ�
	bool SecondCheckFlag() { return second_check_flag; }      //���ɍU���Ɉڂ�
	bool ThirdCheckFlag() { return third_check_flag; }     //�Ō�I���܂ōU���s��


	bool GetJump() { return jump_flag; }

	//�u�[�X�g(����)
	bool GetDushFlag() { return dush_flag; }
	float GetDushStart() { return dush_start; }
	float GetDushEnd() { return dush_end; }

private:
	DX9::SKINNEDMODEL player_model;


	enum
	{
		STAND,
		RUN,
		ACT1,
		ACT2,
		FINISH,
		REBOUND,
		JUMP,
		ROLL,
		DAMAGE1,
		MOTION_MAX
	};

	DX9::SPRITEFONT font;

	float speed;

	//�_�b�V�� �֐�
	bool dush_flag;
	float dush_start;
	float dush_end;

	bool overheart_flag;

	//�W�����v �֐�
	bool jump_flag;
	float jump_time;
	float jump_start_v_;
	//1/2
	const float half = 0.5f;
	//�d�͉����x
	const float gravity_ = 170.0f;
	//����
	const float V0 = 30.5f;


	//�ߐڍU�� �R���{
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

	//�ˌ��U��


private:
	//���N���X����Ăяo��
	Dush_* dush_;


};