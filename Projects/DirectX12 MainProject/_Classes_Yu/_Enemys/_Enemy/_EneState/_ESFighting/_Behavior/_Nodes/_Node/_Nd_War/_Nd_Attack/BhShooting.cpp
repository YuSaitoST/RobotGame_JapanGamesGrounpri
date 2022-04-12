#include "BhShooting.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhShooting::Behavior(const int myID) {
	return EnemyManager::Sertch(myID)->Shooting();
}