#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Dush_
{
public:
	Dush_();
	~Dush_();

	void Update(const float deltaTime);

private:
	bool overheat_falg;
	
};