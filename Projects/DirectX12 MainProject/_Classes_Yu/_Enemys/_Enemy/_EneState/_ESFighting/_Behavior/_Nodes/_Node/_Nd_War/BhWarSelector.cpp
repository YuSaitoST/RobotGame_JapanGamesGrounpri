#include "BhWarSelector.h"
#include "_Nd_Attack/BhShooting.h"
#include "_Nd_Attack/BhAdjacent.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhWarSelector::BhWarSelector() {
	nd_escape_ = new BhEscapeThink();
	nd_random_ = new BhRandSelector(new BhShooting(), new BhAdjacent());
}

BhWarSelector::~BhWarSelector() {
	delete nd_random_;
	delete nd_escape_;
}

Action BhWarSelector::Behavior(const int myID) {
	Action nowAction = (nd_escape_->Behavior(myID) != FAILIRE) ? SUCSESS : nd_random_->Behavior(myID);

	if (nowAction == FAILIRE)
		EnemyManager::Access(myID)->ResetAttackState();

	return nowAction;
}