#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"

class BhEscapeThink : public Node {
public:
	BhEscapeThink();
	virtual ~BhEscapeThink();

	virtual Action Behavior(const int myID) override;
};