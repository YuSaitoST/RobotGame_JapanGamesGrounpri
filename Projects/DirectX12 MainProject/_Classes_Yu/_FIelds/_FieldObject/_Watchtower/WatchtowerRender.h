#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class WatchtowerRender {
public:
	WatchtowerRender() : model_(DX9::MODEL()) {}
	virtual ~WatchtowerRender() {}

	void LoadAsset();
	void Render();

private:
	DX9::MODEL model_;
	int numberOfDome_;
	std::vector<DirectX::XMFLOAT3> posList_;
};