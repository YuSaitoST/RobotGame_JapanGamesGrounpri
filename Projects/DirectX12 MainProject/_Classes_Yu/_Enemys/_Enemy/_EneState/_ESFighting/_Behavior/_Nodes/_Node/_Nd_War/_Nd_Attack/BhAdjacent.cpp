#include "BhAdjacent.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhAdjacent::Behavior(const int myID) {
	return FAILIRE;
	//const float distance = PlayerInfo.GetDistance(EnemyManager::Sertch(myID)->myPosition());
	//const bool certainDistance = (distance <= ENParams.DISTANCE_APPROACHING_PLAYER) && (ENParams.SHORTEST_DISTANCE < distance);

	//if (certainDistance)
	return EnemyManager::Sertch(myID)->Adjacent();
}