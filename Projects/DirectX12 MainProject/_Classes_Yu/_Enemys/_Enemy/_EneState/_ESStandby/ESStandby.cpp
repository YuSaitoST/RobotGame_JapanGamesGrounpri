#include "ESStandby.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

void ESStandby::Update(const int myID) {
	if (PlayerInfo::GetDistance(EnemyManager::Sertch(myID)->myPosition()) <= ENParams.DISTANCE_APPROACHING_PLAYER)
		EnemyManager::Sertch(myID)->SwitchState(FIGHTING);
}