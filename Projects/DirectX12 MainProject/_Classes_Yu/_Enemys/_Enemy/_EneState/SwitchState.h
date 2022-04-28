#pragma once

#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EneStandardParamsLoad/EneStandardParamsLoad.h"
#include "_ESStandby/ESStandby.h"
#include "_ESFighting/ESFighting.h"
#include "_ESStan/ESStan.h"
#include "_ESDown/ESDown.h"

class SwitchStates {
public:
	SwitchStates() {}
	virtual ~SwitchStates() {}

	void Initialize(const int myID);
	EneState* Get(ENE_STATE state);

private:
	ESStandby st_standby_;
	ESFighting st_fighting_;
	ESStan st_stan_;
	ESDown st_down_;
};