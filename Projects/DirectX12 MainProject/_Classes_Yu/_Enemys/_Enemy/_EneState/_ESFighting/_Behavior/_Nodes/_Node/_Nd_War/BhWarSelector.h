#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"
#include "_Nd_Escape/BhEscapeThink.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/BhRandSelector.h"

class BhWarSelector : public Node {
public:
	BhWarSelector();
	virtual ~BhWarSelector();

	virtual Action Behavior(const int myID) override;

private:
	BhEscapeThink* nd_escape_;
	BhRandSelector* nd_random_;
};