#pragma once
#include <random>
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"

class BhSideStep : public Node {
public:
	BhSideStep();
	virtual ~BhSideStep() {}

	virtual Action Behavior(const int myID) override;

private:
	std::mt19937 randomEngine;
	std::uniform_int_distribution<> randomDist;
};