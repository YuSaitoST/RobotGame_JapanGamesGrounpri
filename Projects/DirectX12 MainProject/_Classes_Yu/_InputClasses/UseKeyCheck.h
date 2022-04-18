#pragma once

#include "KeyBoadChecker.h"
#include "GamePadChecker.h"

#define Press UseKeyCheck::GetInstance()

class UseKeyCheck {
public:
	static UseKeyCheck& GetInstance() { return inctance_; }

	void Accepts();

	bool MovePlayerStateUp();
	bool MovePlayerStateDown();
	bool MovePlayerStateRight();
	bool MovePlayerStateLeft();


	bool DushStateKey();
	bool JumpEventKey();

	bool AtackEventKey();
	bool ShotEventKey();

	bool MoveStateLeft();
	bool MoveStateRight();

private:
	UseKeyCheck() {}
	virtual ~UseKeyCheck() {}

	static UseKeyCheck inctance_;
	KeyBoadChecker key_;
	GamePadChecker pad_;
};