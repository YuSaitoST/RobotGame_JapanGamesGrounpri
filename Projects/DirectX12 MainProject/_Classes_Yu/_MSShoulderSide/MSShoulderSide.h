#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

class MSShoulderSide {
public:
	MSShoulderSide(/*float* rotX, float* rotY*/)/* : rotateX_(*rotX), rotateY_(*rotY)*/ {}  // ボーンの回転を参照する
	virtual ~MSShoulderSide() {}

	void LoadAsset(std::wstring fileName);
	void Render();

	void ConvertPosition(Vector3 playerPos, Vector3 shoulderForward);

private:
	const float DIST_FROM_CENTER_TO_SHOULDER = 0.0036f;

	DX9::MODEL shoulder_;
	Vector3 position_;
	//float& rotateX_;
	//float& rotateY_;
};