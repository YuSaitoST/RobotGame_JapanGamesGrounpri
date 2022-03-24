#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#define Lighting MainLight::GetInstance()

class MainLight {
public:
	static MainLight& GetInstance() {
		static MainLight _inctance;
		return _inctance;
	}

	void Setting(const char* name, D3DLIGHT9 light);
	void SetEnable(const char* name, bool enable);
	void Reset() { lightList_.clear(); }

private:
	MainLight() {}
	virtual ~MainLight() {}

	std::vector<char> lightList_;
};