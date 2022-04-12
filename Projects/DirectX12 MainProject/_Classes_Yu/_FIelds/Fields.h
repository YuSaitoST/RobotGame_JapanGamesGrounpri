#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class Fields {
public:
	Fields() {}
	virtual ~Fields() {}

	void LoadAssets();
	void Render();

private:
	DX9::MODEL model_;
};