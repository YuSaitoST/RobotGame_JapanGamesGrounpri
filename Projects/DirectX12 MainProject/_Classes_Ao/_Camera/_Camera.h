#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "_Classes_Yu/_InputClasses/UseKeyCheck.h"


using namespace DirectX;

class _Camera
{
private:
	_Camera();
	~_Camera() {};
public:


	void LoadCSV();
	void LoadAssets(SimpleMath::Vector3 pos);
	void Update(const float deltaTime, SimpleMath::Vector3 pos);
	void Setting(SimpleMath::Vector3 pos);
	void Render();

	DX9::CAMERA GetCamera() { return camera; }
	Vector3 GetCameraForwardVecter() { return camera.GetForwardVector(); }

	static _Camera& GetInstance()
	{
		static _Camera instance;
		return instance;
	}

private:

	DX9::CAMERA camera;
	Vector3 camera_pos_;

	Vector3 pos_bef_;
	Vector3 pos_aft_;
	Vector3 pos_distance_;

	float camera_rotate_speed;

};