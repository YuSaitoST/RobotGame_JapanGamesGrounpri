#include "BhEscapeThink.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/_Nd_War/_Nd_Escape/BhThruster.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhEscapeThink::BhEscapeThink() {
	nd_vsAdj_ = new BhRandSelector(new BhThruster(), new BhBackStep());
	nd_vsShoot_ = new BhBackStep();
	interval_ = new OriTimer(2.0f);

	lastAction_ = FAILIRE;
	playerAttackState_ = AttackState::None_Attack;
}

BhEscapeThink::~BhEscapeThink() {
	delete interval_;
	delete nd_vsShoot_;
	delete nd_vsAdj_;
}

Action BhEscapeThink::Behavior(const int myID) {
	// Player‚ªUŒ‚‚µ‚Ä‚¢‚é‚È‚ç
	// ‹ßÚUŒ‚‚©ŽËŒ‚UŒ‚‚©‚Å•ªŠò‚·‚é

	if (lastAction_ == REPEAT) {
		if (playerAttackState_ == AttackState::Adjacent)
			lastAction_ = nd_vsAdj_->Behavior(myID);
		else if (playerAttackState_ == AttackState::Shooting)
			lastAction_ = nd_vsShoot_->Behavior(myID);

		return lastAction_;
	}

	playerAttackState_ = PlayerInfo.NowAttackState();

	if (playerAttackState_ == AttackState::Adjacent)
		lastAction_ = nd_vsAdj_->Behavior(myID);
	else if (playerAttackState_ == AttackState::Shooting)
		lastAction_ = nd_vsShoot_->Behavior(myID);
	else
		lastAction_ = FAILIRE;

	return lastAction_;
}