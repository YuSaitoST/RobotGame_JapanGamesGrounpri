#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"

class BhMove : public Node {
public:
	BhMove() {};
	virtual ~BhMove() {}

	virtual Action Behavior(const int myID) override;
};