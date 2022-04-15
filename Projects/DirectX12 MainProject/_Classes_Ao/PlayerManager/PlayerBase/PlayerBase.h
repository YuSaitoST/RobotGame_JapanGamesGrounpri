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
	~PlayerBase() {};

	void Initialize();
	void LoadModel();
	void LoadEffect();

	void Setting();

	void Move_Front(const float deltaTime);
	void Move_Back(const float deltaTime);
	void Move_Right(const float deltaTime);
	void Move_Left(const float deltaTime);


	void Attack(const float deltaTime) {};
	void Shot(const float deltaTime) {};
	void Dush(const float deltaTime);
	void Jump(const float deltaTime);

	void Render();
	void _2D();

	DX9::SKINNEDMODEL& GetModel() { return player_model; }
	SimpleMath::Vector3* GetPlayer_Pos() { return &player_pos; }
	bool GetJump() { return jump_flag; }

	//ブースト(加速)
	bool GetDushFlag() { return dush_flag; }
	float GetDushStart() { return dush_start; }
	float GetDushEnd() { return dush_end; }

private:
	DX9::SKINNEDMODEL player_model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	OBJ_TYPE player;
	int player_tag = 0;

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


private:
	//他クラスから呼び出す
	Dush_* dush_;


};