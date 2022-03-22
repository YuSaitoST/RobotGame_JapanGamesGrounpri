#pragma once

#include "Base/dxtk.h"
#include "Base/pch.h"

#define Light MainLight::GetInstance()

class MainLight {
public:
	static MainLight& GetInstance() {
		static MainLight _inctance;
		return _inctance;
	}

	void Set();
	void Enable(bool enable);

private:
	MainLight() { Initialize(); }
	virtual ~MainLight() {}

	void Initialize();

	D3DLIGHT9 light_;
};