#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class DomeRender {
public:
	DomeRender() : model_(DX9::MODEL()) {}
	virtual ~DomeRender() {}

	void LoadAsset();
	void Render();

private:
	DX9::MODEL model_;
	int numberOfDome_;
	std::vector<DirectX::XMFLOAT3> posList_;
};