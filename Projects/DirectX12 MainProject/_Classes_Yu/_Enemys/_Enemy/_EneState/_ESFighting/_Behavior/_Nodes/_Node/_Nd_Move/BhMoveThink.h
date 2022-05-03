#pragma once

#include <random>
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"
#include "BhMove.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/_Nd_War/_Nd_Escape/BhBackStep.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/_Nd_War/_Nd_Escape/BhSideStep.h"

class BhMoveThink : public Node {
public:
	BhMoveThink();
	virtual ~BhMoveThink();

	virtual Action Behavior(const int myID) override;

private:
	Node* NewActToBeTaken(Node* node);

	const int PROBABILITY_OF_NOT_STEP[2] = { 65,25 };
	const float MELEEATTACK_TO_DIST_MIN = 1.0f;

	BhMove* nd_move_;
	BhBackStep* nd_backStep_;
	BhSideStep* nd_sideStep_;
	Node* lastNode_;
	Action lastAction_;

	std::mt19937 randomEngine_;
	std::uniform_int_distribution<> randomDist_;
};