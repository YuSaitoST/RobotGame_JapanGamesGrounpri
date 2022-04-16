#include "BhMove.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhMove::Behavior(const int myID) {
	return EnemyManager::Access(myID)->Move(PlayerInfo.GetDirection(EnemyManager::Access(myID)->myPosition()));
}