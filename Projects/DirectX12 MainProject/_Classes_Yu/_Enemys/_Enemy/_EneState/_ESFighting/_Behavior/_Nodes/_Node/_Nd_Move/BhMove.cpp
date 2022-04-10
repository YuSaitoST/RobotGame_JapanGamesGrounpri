#include "BhMove.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhMove::Behavior(const int myID) {
	EnemyManager::Sertch(myID)->Move(PlayerInfo::GetDirection(EnemyManager::Sertch(myID)->myPosition()));
	return SUCSESS;
}