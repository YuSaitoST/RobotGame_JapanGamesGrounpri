#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "_Classes_Yu/_Enemys/_EneParamsLoad/EneParamsLoad.h"
#include "_Classes_Yu/_Enemys/_Instructor/EneInstructor.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"

class EneState {
public:
	EneState() {}
	virtual ~EneState() {}

	virtual void Update(const int myID) = 0;
};