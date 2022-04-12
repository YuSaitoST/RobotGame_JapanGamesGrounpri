#include "BhMoveThink.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhMoveThink::BhMoveThink() {
	nd_move_ = new BhMove();
}

BhMoveThink::~BhMoveThink() {
	delete nd_move_;
}

Action BhMoveThink::Behavior(const int myID) {
	const float distance = PlayerInfo.GetDistance(EnemyManager::Sertch(myID)->myPosition());
	const bool certainDistance = (distance <= ENParams.DISTANCE_APPROACHING_PLAYER) && (ENParams.SHORTEST_DISTANCE < distance);
	if (certainDistance)
		return nd_move_->Behavior(myID);
	return FAILIRE;
}