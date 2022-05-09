#include "BhAdjacent.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhAdjacent::Behavior(const int myID) {
	Enemy* enemy				= EnemyManager::Access(myID);
	const float distance		= PlayerInfo.GetDistance(enemy->myPosition());
	const bool certainDistance	= (ENParams.UNAPPROACHABLE_DISTANCE < distance) && (distance <= ENParams.RANGE_OF_MELEEATTACK);

	if (certainDistance)
		return enemy->Adjacent();

	return FAILIRE;
}