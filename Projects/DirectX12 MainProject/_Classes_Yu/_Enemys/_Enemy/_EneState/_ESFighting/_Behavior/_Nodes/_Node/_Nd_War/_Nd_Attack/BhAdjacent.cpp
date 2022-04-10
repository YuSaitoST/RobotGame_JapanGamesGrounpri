#include "BhAdjacent.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhAdjacent::BhAdjacent() {

}

BhAdjacent::~BhAdjacent() {

}

Action BhAdjacent::Behavior(const int myID) {
	EnemyManager::Sertch(myID)->Adjacent();
	return SUCSESS;
}