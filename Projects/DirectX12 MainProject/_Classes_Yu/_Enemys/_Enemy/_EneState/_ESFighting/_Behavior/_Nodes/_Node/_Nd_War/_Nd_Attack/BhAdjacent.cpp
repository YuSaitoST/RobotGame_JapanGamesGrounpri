#include "BhAdjacent.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhAdjacent::Behavior(const int myID) {
	const float distance = PlayerInfo.GetDistance(EnemyManager::Access(myID)->myPosition());
	const bool certainDistance = (distance <= ENParams.MELEEATTACK_TO_DISTANCE);// && (ENParams.SHORTEST_DISTANCE <= distance);

	if (certainDistance)
		return EnemyManager::Access(myID)->Adjacent();

	return FAILIRE;
}