#pragma once

class HPGauge {
public:
	HPGauge(const int maxHP) : hp_(maxHP) {}
	virtual ~HPGauge() {}

	void TakeDamage(int damage) { hp_ -= damage; }
	int GetHP() const { return hp_; }

private:
	int hp_;
};