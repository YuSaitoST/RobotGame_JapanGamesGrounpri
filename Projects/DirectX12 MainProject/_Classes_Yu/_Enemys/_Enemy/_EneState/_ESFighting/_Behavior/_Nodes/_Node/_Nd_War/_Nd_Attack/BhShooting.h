#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"

class BhShooting : public Node {
public:
	BhShooting();
	virtual ~BhShooting();

	virtual Action Behavior(const int myID) override;
};