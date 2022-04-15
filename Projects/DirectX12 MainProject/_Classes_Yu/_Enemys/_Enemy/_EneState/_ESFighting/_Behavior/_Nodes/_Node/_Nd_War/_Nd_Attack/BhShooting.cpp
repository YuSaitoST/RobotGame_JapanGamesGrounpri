#include "BhShooting.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhShooting::Behavior(const int myID) {
	const float distance = PlayerInfo.GetDistance(EnemyManager::Sertch(myID)->myPosition());
	const bool certainDistance = (distance <= ENParams.RANGE_OF_SHOT) && (ENParams.SHORTEST_DISTANCE < distance);

	if (certainDistance)
		return EnemyManager::Sertch(myID)->Shooting();

	return Action::FAILIRE;
}