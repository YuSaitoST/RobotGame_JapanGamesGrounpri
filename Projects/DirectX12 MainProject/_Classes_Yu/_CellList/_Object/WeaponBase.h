#pragma once

#include "ObjectBase.h"

class WeaponBase : public ObjectBase {
public:
	WeaponBase() : damage_(0.f) {}
	virtual ~WeaponBase() {}

	float GetDamage() const { return damage_; }

protected:
	float damage_;
};