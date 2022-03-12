#include "UseKeyCheck.h"

UseKeyCheck UseKeyCheck::inctance_;

void UseKeyCheck::Accepts() {
	key_.Accepts();
	pad_.Accepts(0);
}

bool UseKeyCheck::MoveStateLeft() {
	return key_.StateArrowKey(ARROW_KEY::K_LEFT) || pad_.StateOnOffKey(0, PAD::P_LEFT);
}

bool UseKeyCheck::MoveStateRight() {
	return key_.StateArrowKey(ARROW_KEY::K_RIGHT) || pad_.StateOnOffKey(0, PAD::P_RIGHT);
}