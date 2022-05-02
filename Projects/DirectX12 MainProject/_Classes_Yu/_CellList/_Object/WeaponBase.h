#pragma once

#include "ObjectBase.h"

class WeaponBase : public ObjectBase {
public:
	WeaponBase() : damage_(0.f), isAttack_(false) {}
	virtual ~WeaponBase() {}

	void ChangeAttackState(const bool attack) { isAttack_ = attack; }

	float GetDamage() const { return damage_; }
	bool IsBeenAttack() const { return isAttack_; }

protected:
	float damage_;
	bool isAttack_;
};