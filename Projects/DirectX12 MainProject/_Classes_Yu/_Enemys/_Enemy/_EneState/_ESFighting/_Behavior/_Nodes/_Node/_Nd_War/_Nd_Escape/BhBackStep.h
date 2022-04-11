#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"

class BhBackStep : public Node {
public:
	BhBackStep() {}
	virtual ~BhBackStep() {}

	virtual Action Behavior(const int myID) override;
};