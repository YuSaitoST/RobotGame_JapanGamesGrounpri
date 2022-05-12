#include "UseKeyCheck.h"

UseKeyCheck UseKeyCheck::inctance_;

void UseKeyCheck::Accepts() {
	key_.Accepts();
	pad_.Accepts(0);
}


bool UseKeyCheck::RotateStateRight() {
	return key_.StateCharaKey('P');
}
bool UseKeyCheck::RotateStateLeft() {
	return key_.StateCharaKey('O');
}


bool UseKeyCheck::DushStateKey() {
	return key_.StateCharaKey('S');
}

bool UseKeyCheck::JumpEventKey() {
	return key_.EventCharaKey('D');
}

bool UseKeyCheck::AtackEventKey() {
	return key_.EventCharaKey('A');
}

bool UseKeyCheck::ShotEventKey() {
	return key_.EventCharaKey('Z');
}

bool UseKeyCheck::MoveStateLeft() {
	return key_.StateArrowKey(ARROW_KEY::K_LEFT) || pad_.StateOnOffKey(0, PAD::P_LEFT);
}

bool UseKeyCheck::MoveStateRight() {
	return key_.StateArrowKey(ARROW_KEY::K_RIGHT) || pad_.StateOnOffKey(0, PAD::P_RIGHT);
}

Vector2 UseKeyCheck::DirectionKey() {
	return key_.StateDirection();
}

bool UseKeyCheck::RotateLeftCameraKey() {
	return key_.StateCharaKey('Q');
}
bool UseKeyCheck::RotateRightCameraKey() {
	return key_.StateCharaKey('W');
}
