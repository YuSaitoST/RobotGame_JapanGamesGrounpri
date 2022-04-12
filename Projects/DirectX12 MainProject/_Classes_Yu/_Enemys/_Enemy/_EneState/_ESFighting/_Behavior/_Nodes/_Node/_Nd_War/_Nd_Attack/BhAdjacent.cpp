#include "BhAdjacent.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhAdjacent::Behavior(const int myID) {
	return EnemyManager::Sertch(myID)->Adjacent();
}