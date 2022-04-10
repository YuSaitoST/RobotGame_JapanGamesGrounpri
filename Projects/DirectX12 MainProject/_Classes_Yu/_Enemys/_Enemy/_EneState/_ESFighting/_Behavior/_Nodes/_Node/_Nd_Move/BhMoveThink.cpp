#include "BhMoveThink.h"
#include "BhMove.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhMoveThink::BhMoveThink() {
	next_ = new BhMove();
}

BhMoveThink::~BhMoveThink() {
	delete next_;
}

Action BhMoveThink::Behavior(const int myID) {
	const float distance = PlayerInfo::GetDistance(EnemyManager::Sertch(myID)->myPosition());
	if ((distance <= ENParams.DISTANCE_APPROACHING_PLAYER) && (ENParams.SHORTEST_DISTANCE < distance))
		return next_->Behavior(myID);
	return FAILIRE;
}