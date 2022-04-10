#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"

class BhAdjacent : public Node {
public:
	BhAdjacent();
	virtual ~BhAdjacent();

	virtual Action Behavior(const int myID) override;
};