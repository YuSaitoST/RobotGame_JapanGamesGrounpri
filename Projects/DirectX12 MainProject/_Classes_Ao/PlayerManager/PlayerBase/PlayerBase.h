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
	//アニメーション
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

	float camera_rotate_speed;//カメラの回転速度
	float player_spped;//プレイヤーのスピード()
	float normal_speed;//プレイヤーの通常のスピード
	

	//ダッシュ 関数 系統
	//ブースト時の変数
	int   boost_zero;//ブーストの初期値
	int   boost_max; //ブーストの最大値
	float boost_dush;//ブースト時の速度
	bool  boost_flag;//ブーストしているかのフラグ

	//オーバーヒート時の変数
	bool overheart_flag; //オーバーヒートのフラグ
	float overheart_time;//オーバーヒートしている時間 初期値
	float overheart_max; //オーバーヒートしている時間 最大値
	float overheart_speed = 5.0f;//オーバーヒート時のスピード

	float PlayerSpeedMode();

	

	//ジャンプ 関数
	bool jump_flag = false;
	float jump_time = 0.0f;
	float jump_start_v_ = 0.0f;
	//1/2
	float half = 0.5f;
	//重力加速度
	float gravity_ = 50.0f;
	//初速
	float V0 = 40.0f;

	//近接攻撃 コンボ
	enum  BURST_STATE
	{
		NOT_BURST,
		FIRST,
		SECOND,
		THIRD
	};
	BURST_STATE burst_state_mode;
	 
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

	//射撃
	int shotdamage;
	
};