#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_SkyDome/SkyDome.h"
#include "_FieldObject/_Dome/DomeRender.h"

class Fields {
public:
	Fields();
	virtual ~Fields();

	void LoadAssets();
	void Render();

private:
	SkyDome* skyDome_;
	DomeRender* domes_;
	DX9::MODEL model_;

	DX9::TEXTURE bump_;
	DX9::SHADER shader_;
};
