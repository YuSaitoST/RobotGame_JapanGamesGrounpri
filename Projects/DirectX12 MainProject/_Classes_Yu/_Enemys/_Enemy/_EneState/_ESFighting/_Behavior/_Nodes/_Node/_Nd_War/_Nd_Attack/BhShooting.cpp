#include "BhShooting.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhShooting::Behavior(const int myID) {
	const float distance = PlayerInfo.GetDistance(EnemyManager::Access(myID)->myPosition());
	const bool certainDistance = (ENParams.SWITCH_TO_MELEEATTACK < distance) && (distance <= ENParams.RANGE_OF_SHOT);

	if (certainDistance)
		return EnemyManager::Access(myID)->Shooting();

	return Action::FAILIRE;
}