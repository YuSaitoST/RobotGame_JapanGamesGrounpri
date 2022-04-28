#include "SwitchState.h"

void SwitchStates::Initialize(const int myID) {
	st_standby_.Initialize(myID);
}

EneState* SwitchStates::Get(ENE_STATE state) {
	switch (state) {
		case STANDBY	: return &st_standby_;
		case FIGHTING	: return &st_fighting_;
		case STAN		: return &st_stan_;
		case DOWN		: return &st_down_;
		default			: assert(!"Enemy : ˆÙí‚Èó‘Ô");
	}
}