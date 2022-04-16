#include "BhShooting.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhShooting::Behavior(const int myID) {
	const float distance = PlayerInfo.GetDistance(EnemyManager::Access(myID)->myPosition());
	const bool certainDistance = (distance <= ENParams.RANGE_OF_SHOT) && (ENParams.SWITCH_TO_MELEEATTACK < distance);

	if (certainDistance)
		return EnemyManager::Access(myID)->Shooting();

	return Action::FAILIRE;
}