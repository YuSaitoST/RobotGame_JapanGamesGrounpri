#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	void Initialize();
	void Update(const float deltaTime);
	void Render();

private:
	DX9::CAMERA camera;
};