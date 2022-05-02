#include "BhEscapeThink.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhEscapeThink::BhEscapeThink() {
	nd_vsAdj_	= new BhRandSelector(new BhSideStep(), new BhBackStep());
	nd_vsShoot_ = new BhSideStep();
	interval_	= new OriTimer(2.0f);

	lastAction_ = FAILIRE;
	playerAttackState_ = AttackState::None_Attack;
	stepCount_ = 0;
}

BhEscapeThink::~BhEscapeThink() {
	delete interval_;
	delete nd_vsShoot_;
	delete nd_vsAdj_;
}

Action BhEscapeThink::Behavior(const int myID) {
	const bool a_certain_distance_away = ENParams.DISTANCE_APPROACHING_PLAYER < PlayerInfo.GetDistance(EnemyManager::Access(myID)->myPosition());

	// 一定以上離れていて、行動していないなら
	if ((lastAction_ != Action::REPEAT) && a_certain_distance_away)
		return Action::FAILIRE;

	// 連続ステップが終了したら
	if (2 <= stepCount_) {
		stepCount_ = 0;
		return lastAction_ = FAILIRE;
	}

	lastAction_ = Act(myID);

	// ステップ回数をカウント
	if (lastAction_ == SUCSESS) {
		lastAction_ = REPEAT;
		stepCount_ += 1;
	}

	return lastAction_;
}

Action BhEscapeThink::Thinks(const int myID) {
	if (playerAttackState_ == AttackState::Adjacent)
		return nd_vsAdj_->Behavior(myID);
	else if (playerAttackState_ == AttackState::Shooting)
		return nd_vsShoot_->Behavior(myID);
	else
		return FAILIRE;
}

Action BhEscapeThink::Act(const int myID) {
	if (lastAction_ == REPEAT)
		return Thinks(myID);

	playerAttackState_ = PlayerInfo.NowAttackState();

	return Thinks(myID);
}