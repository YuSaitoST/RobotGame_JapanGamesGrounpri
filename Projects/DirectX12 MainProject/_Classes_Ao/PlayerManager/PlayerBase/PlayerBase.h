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
	//アニメーション
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);


	DX9::SKINNEDMODEL& GetModel() { return player_model; }
	SimpleMath::Vector3* GetPlayer_Pos() { return &pos_; }

	//攻撃
	enum AtackMode
	{
		MeleeAttack, //近接攻撃
		ShotAttack   //射撃
	};
	AtackMode attack_mode_state;
	AtackMode AtackState() { return attack_mode_state; }

	//近接攻撃 コンボ
    //三連撃
	enum  BURST_STATE
	{
		NOT_BURST,
		FIRST,
		SECOND,
		THIRD
	};
	BURST_STATE burst_state_mode;
	BURST_STATE BurstState() { return burst_state_mode; }

	//コンボ　受付時間 関数
	float GetFristReceptionTime() { return frist_reception_time; }
	float GetSecondReceptionTime() { return second_reception_time; }
	float GetThirdReceptionTime() { return third_reception_time; }

	//コンボ　入力　関数
	bool FristCheckFlag() { return frist_check_flag; }     //次に攻撃に移る
	bool SecondCheckFlag() { return second_check_flag; }      //次に攻撃に移る
	bool ThirdCheckFlag() { return third_check_flag; }     //最後終わるまで攻撃不可


	bool GetJump() { return jump_flag; }

	//ブースト(加速)
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

	//ダッシュ 関数
	bool dush_flag;
	float dush_start;
	float dush_end;

	bool overheart_flag;

	//ジャンプ 関数
	bool jump_flag;
	float jump_time;
	float jump_start_v_;
	//1/2
	const float half = 0.5f;
	//重力加速度
	const float gravity_ = 170.0f;
	//初速
	const float V0 = 30.5f;


	//近接攻撃 コンボ
	//一撃目
	float frist_reception_time; //受付時間初期値
	float frist_reception_max;  //受付時間最大値
	bool  frist_check_flag;     //次に攻撃に移る

	//二撃目
	float second_reception_time; //受付時間初期値
	float second_reception_max;   //受付時間最大値
	bool  second_check_flag;      //次に攻撃に移る


	//三撃目
	float third_reception_time; //受付時間初期値
	float third_reception_max;  //受付時間最大値
	bool  third_check_flag;     //最後終わるまで攻撃不可

	//射撃攻撃


private:
	//他クラスから呼び出す
	Dush_* dush_;


};