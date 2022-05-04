#include "BhShooting.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhShooting::Behavior(const int myID) {
	Enemy* enemy = EnemyManager::Access(myID);
	const float distance = PlayerInfo.GetDistance(enemy->myPosition());
	const bool certainDistance = (ENParams.RANGE_OF_MELEEATTACK < distance) && (distance <= ENParams.RANGE_OF_SHOOTING);

	if (certainDistance)
		return enemy->Shooting();
	else
		enemy->ResetAttackState();

	return Action::FAILIRE;
}