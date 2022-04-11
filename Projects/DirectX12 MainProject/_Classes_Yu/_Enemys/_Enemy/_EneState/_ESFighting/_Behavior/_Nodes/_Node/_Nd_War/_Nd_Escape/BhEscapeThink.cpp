#include "BhEscapeThink.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/_Nd_War/_Nd_Escape/BhThruster.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhEscapeThink::BhEscapeThink() {
	nd_vsAdj_ = new BhRandSelector(new BhThruster(), new BhBackStep());
	nd_vsShoot_ = new BhBackStep();

	lastAction_ = FAILIRE;
}

BhEscapeThink::~BhEscapeThink() {
	delete nd_vsShoot_;
	delete nd_vsAdj_;
}

Action BhEscapeThink::Behavior(const int myID) {
	// Playerが攻撃しているなら
	// 近接攻撃か射撃攻撃かで分岐する

	if (lastAction_ == REPEAT) {
		if (lastActionState_)
			lastAction_ = nd_vsAdj_->Behavior(myID);
		else
			lastAction_ = nd_vsShoot_->Behavior(myID);

		return lastAction_;
	}

	//if ()
	//	lastAction_ = nd_vsAdj_->Behavior(myID);
	//else if ()
	//	lastAction_ = nd_vsShoot_->Behavior(myID);
	//else
	//	lastAction_ = FAILIRE;

	// lastActionState_の更新必要
	return lastAction_;
}