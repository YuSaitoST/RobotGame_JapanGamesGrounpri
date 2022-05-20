#include "UseKeyCheck.h"

UseKeyCheck UseKeyCheck::inctance_;

void UseKeyCheck::Accepts() {
	key_.Accepts();
	pad_.Accepts(0);
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

//à⁄ìÆÇÃÉLÅ[
bool UseKeyCheck::MoveForwardStateKey() {
	return key_.StateCharaKey('W');
}
bool UseKeyCheck::MoveBackwardStateKey() {
	return key_.StateCharaKey('S');
}
bool UseKeyCheck::MoveRightStateKey() {
	return key_.StateCharaKey('D');
}
bool UseKeyCheck::MoveLeftStateKey() {
	return key_.StateCharaKey('A');
}


bool UseKeyCheck::RotateLeftCameraKey() {
	return key_.StateArrowKey(ARROW_KEY::K_LEFT);
}
bool UseKeyCheck::RotateRightCameraKey() {
	return key_.StateArrowKey(ARROW_KEY::K_RIGHT);
}
