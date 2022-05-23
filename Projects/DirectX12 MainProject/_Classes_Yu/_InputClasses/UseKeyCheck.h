#pragma once

#include "KeyBoadChecker.h"
#include "GamePadChecker.h"

#define Press UseKeyCheck::GetInstance()

class UseKeyCheck {
public:
	static UseKeyCheck& GetInstance() { return inctance_; }

	void Accepts();


	bool DushStateKey();
	bool JumpEventKey();

	bool AtackEventKey();
	bool ShotEventKey();

	bool MoveStateLeft();
	bool MoveStateRight();

	Vector2 MoveDirection();
	Vector2 DirectionKey();
	//カメラのキー
	bool RotateLeftCameraKey();
	bool RotateRightCameraKey();

	//移動のキー
	bool MoveForwardStateKey();
	bool MoveBackwardStateKey();
	bool MoveRightStateKey();
	bool MoveLeftStateKey();

private:
	UseKeyCheck() {}
	virtual ~UseKeyCheck() {}

	static UseKeyCheck inctance_;
	KeyBoadChecker key_;
	GamePadChecker pad_;
};