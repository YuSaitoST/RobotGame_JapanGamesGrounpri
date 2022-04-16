#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_SkyDome/SkyDome.h"

class Fields {
public:
	Fields();
	virtual ~Fields();

	void LoadAssets();
	void Render();

private:
	SkyDome* skyDome_;
	DX9::MODEL model_;
};