#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/BhRandSelector.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/_Nd_War/_Nd_Escape/BhBackStep.h"


class BhEscapeThink : public Node {
public:
	BhEscapeThink();
	virtual ~BhEscapeThink();

	virtual Action Behavior(const int myID) override;

private:
	BhRandSelector* nd_vsAdj_;
	BhBackStep* nd_vsShoot_;

	Action lastAction_;
	bool lastActionState_;
};