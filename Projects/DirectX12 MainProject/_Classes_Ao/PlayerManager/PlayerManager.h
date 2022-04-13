#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes_Yu/_InputClasses/UseKeyCheck.h"
#include "_Classes_Ao/PlayerManager/PlayerBase/PlayerBase.h"


using namespace DirectX;

class PlayerManager
{
public:
	PlayerManager(){};
	~PlayerManager(){};

	void Initialize();
	void LoadModel();

	void Update(const float deltaTime);
	void Render();

	void _2D();
	

private:
	PlayerBase p_base_;

	DX9::CAMERA camera;

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



};