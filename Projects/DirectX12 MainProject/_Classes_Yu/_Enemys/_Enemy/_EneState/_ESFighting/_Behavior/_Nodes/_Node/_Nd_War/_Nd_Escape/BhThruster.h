#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"

class BhThruster : public Node {
public:
	BhThruster();
	virtual ~BhThruster();

	virtual Action Behavior(const int myID) override;
};