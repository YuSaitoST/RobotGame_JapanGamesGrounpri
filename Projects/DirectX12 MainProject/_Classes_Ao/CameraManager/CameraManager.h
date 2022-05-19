#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "_Classes_Ao/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;

class CameraManager
{
public:
	CameraManager(){};
	~CameraManager(){};

	void Initialize();
	void LoadAsset();
	void Update();
	void Render();

private:
	DX9::CAMERA camera;

	//PlayerBase player_;
};