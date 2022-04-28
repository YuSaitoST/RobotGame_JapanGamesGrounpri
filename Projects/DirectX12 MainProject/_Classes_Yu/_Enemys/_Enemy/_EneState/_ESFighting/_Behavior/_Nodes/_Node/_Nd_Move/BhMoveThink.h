#pragma once

#include <random>
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"
#include "BhMove.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/BhRandSelector.h"

class BhMoveThink : public Node {
public:
	BhMoveThink();
	virtual ~BhMoveThink();

	virtual Action Behavior(const int myID) override;

private:
	const int PROBABILITY_OF_NOT_STEP[2] = { 20,5 };

	BhMove* nd_move_;
	BhRandSelector* nd_backStep_;
	Node* lastNode_;
	Action lastAction_;

	std::mt19937 randomEngine_;
	std::uniform_int_distribution<> randomDist_;
};