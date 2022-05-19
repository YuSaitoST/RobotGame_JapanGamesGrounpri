#include "BhAdjacent.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhAdjacent::Behavior(const int myID) {
	Enemy* enemy				= EnemyManager::Access(myID);
	const float distance		= PlayerInfo.GetDistance(enemy->myPosition());
	const bool certainDistance	= (ENParams.UNAPPROACHABLE_DISTANCE < distance) && (distance <= ENParams.RANGE_OF_MELEEATTACK);
	const bool TooClose			= distance <= ENParams.UNAPPROACHABLE_DISTANCE;

	if (TooClose)
		return Action::FAILIRE;
	else if (certainDistance)
		return enemy->Adjacent();
	else
		enemy->ResetAttackState();

	return Action::FAILIRE;
}