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
	virtual ~PlayerManager(){};

	void Initialize();
	void LoadModel();

	void Update(const float deltaTime);
	void Render();

	void _2D();
	

private:
	PlayerBase p_base_;

	DX9::CAMERA camera;
	Vector3 camera_pos_;
	Vector3 camera_angle;

	Vector3 pos_bef_;
	Vector3 pos_aft_;
	Vector3 pos_distance_;
	

	DX9::SPRITEFONT font;


};