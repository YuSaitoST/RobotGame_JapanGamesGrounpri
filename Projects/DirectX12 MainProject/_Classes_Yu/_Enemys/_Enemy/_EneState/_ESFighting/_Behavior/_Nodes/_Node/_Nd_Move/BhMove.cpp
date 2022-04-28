#include "BhMove.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhMove::Behavior(const int myID) {
	Enemy* enemy = EnemyManager::Access(myID);
	return enemy->Move(PlayerInfo.GetDirection(enemy->myPosition()));
}