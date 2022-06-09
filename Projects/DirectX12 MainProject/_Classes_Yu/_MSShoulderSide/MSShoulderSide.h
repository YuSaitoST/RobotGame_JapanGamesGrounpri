#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class MSShoulderSide {
public:
	MSShoulderSide() {}
	virtual ~MSShoulderSide() {}

	void Initialize(/*float* rotX, float* rotY*/);
	void LoadAsset(std::wstring fileName);
	void Render(DirectX::SimpleMath::Vector3 playerPos, DirectX::SimpleMath::Vector3 shoulderForward);

private:
	DirectX::XMFLOAT3 ConvertPosition(DirectX::SimpleMath::Vector3 playerPos, DirectX::SimpleMath::Vector3 shoulderForward);

	const float DIST_FROM_CENTER_TO_SHOULDER_JEGAN = 0.0036f;

	DX9::MODEL shoulder_;
	//float& rotateX_;	//! 上腕のボーンのX軸回転を
	//float& rotateY_;	//! 腰のY軸回転を入れる(回転自体同じだから)
};