#include "UseKeyCheck.h"

UseKeyCheck UseKeyCheck::inctance_;

void UseKeyCheck::Accepts() {
	key_.Accepts();
	pad_.Accepts(0);
}


bool UseKeyCheck::RotateStateRight() {
	return key_.StateOnOffKey(CKEY::P);
}
bool UseKeyCheck::RotateStateLeft() {
	return key_.StateOnOffKey(CKEY::O);
}


bool UseKeyCheck::DushStateKey() {
	return key_.StateOnOffKey(CKEY::S);
}

bool UseKeyCheck::JumpEventKey() {
	return key_.EventOnOffKey(SKEY::SPACE);
}

bool UseKeyCheck::AtackEventKey() {
	return key_.EventOnOffKey(CKEY::A);
}

bool UseKeyCheck::ShotEventKey() {
	return key_.EventOnOffKey(CKEY::Z);
}

bool UseKeyCheck::MoveStateLeft() {
	return key_.StateOnOffKey(SKEY::LEFT) || pad_.StateOnOffKey(0, PAD::P_LEFT);
}

bool UseKeyCheck::MoveStateRight() {
	return key_.StateOnOffKey(SKEY::RIGHT) || pad_.StateOnOffKey(0, PAD::P_RIGHT);
}

Vector2 UseKeyCheck::MoveDirection() {
	Vector2 direction = Vector2::Zero;
	direction.x = key_.StateOnOffKey(SKEY::LEFT) ? -1 : key_.StateOnOffKey(SKEY::RIGHT) ? 1 : 0;
	direction.x = key_.StateOnOffKey(SKEY::DOWN) ? -1 : key_.StateOnOffKey(SKEY::UP) ? 1 : 0;
	direction.Normalize();
	return direction;
}

Vector2 UseKeyCheck::DirectionKey() {
	return key_.StateDirection();
}

bool UseKeyCheck::RotateLeftCameraKey() {
	return key_.StateOnOffKey(CKEY::Q);
}
bool UseKeyCheck::RotateRightCameraKey() {
	return key_.StateOnOffKey(CKEY::W);
}
