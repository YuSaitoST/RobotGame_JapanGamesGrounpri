#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"
#include "BhMove.h"

class BhMoveThink : public Node {
public:
	BhMoveThink();
	virtual ~BhMoveThink();

	virtual Action Behavior(const int myID) override;

private:
	BhMove* nd_move_;
	Action lastAction_;
};