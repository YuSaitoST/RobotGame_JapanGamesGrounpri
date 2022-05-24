#include "SwitchState.h"

void SwitchStates::Initialize(const int myID) {
	st_standby_.Initialize(myID);
}

EneState* SwitchStates::Get(ENE_STATE state) {
	switch (state) {
	case ENE_STATE::STANDBY	: return &st_standby_;
	case ENE_STATE::FIGHTING	: return &st_fighting_;
	case ENE_STATE::STAN		: return &st_stan_;
	case ENE_STATE::DOWN		: return &st_down_;
	default			: assert(!"Enemy : àŸèÌÇ»èÛë‘");
	}
}