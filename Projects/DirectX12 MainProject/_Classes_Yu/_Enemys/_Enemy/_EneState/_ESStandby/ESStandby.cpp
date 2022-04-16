#include "ESStandby.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

void ESStandby::Update(const int myID) {
	if (PlayerInfo.GetDistance(EnemyManager::Access(myID)->myPosition()) <= ENParams.DISTANCE_APPROACHING_PLAYER)
		EnemyManager::Access(myID)->SwitchState(FIGHTING);
}