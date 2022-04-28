#pragma once

#include "_Classes_Yu/_CellList/_Object/AttackState.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/BhRandSelector.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/_Nd_War/_Nd_Escape/BhSideStep.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/_Nd_War/_Nd_Escape/BhBackStep.h"
#include "_Classes_Yu/_UI/_OriTimer/OriTimer.h"

class BhEscapeThink : public Node {
public:
	BhEscapeThink();
	virtual ~BhEscapeThink();

	virtual Action Behavior(const int myID) override;

private:
	Action Thinks(const int myID);
	Action Act(const int myID);

	BhRandSelector* nd_vsAdj_;
	BhSideStep* nd_vsShoot_;
	OriTimer* interval_;

	Action lastAction_;
	AttackState playerAttackState_;
	int stepCount_;
};