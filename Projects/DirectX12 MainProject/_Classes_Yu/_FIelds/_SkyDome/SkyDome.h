#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class SkyDome {
public:
	SkyDome() {}
	virtual ~SkyDome() {}

	void LoadAsset();
	void Render(const DirectX::SimpleMath::Vector3 pos);

private:
	DX9::MODEL model_;
};