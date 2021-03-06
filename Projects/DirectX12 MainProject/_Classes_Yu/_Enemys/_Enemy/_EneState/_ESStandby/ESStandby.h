#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/EneState.h"

class Enemy;
class ESStandby final : public EneState {
public:
	ESStandby() : isMoveRight_(true) {}
	virtual ~ESStandby() {}

	void Initialize(const int myID);
	virtual void Update(const int myID) override;

private:
	void SertchUnit();
	void UpperUnit();

	const Vector3 DIRECTION[2] = { Vector3::Left, Vector3::Right };

	Enemy* enemy_;
	int positionID_;
	bool isMoveRight_;
};