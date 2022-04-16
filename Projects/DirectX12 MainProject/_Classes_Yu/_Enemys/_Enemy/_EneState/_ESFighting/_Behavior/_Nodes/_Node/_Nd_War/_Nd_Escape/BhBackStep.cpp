#include "BhBackStep.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

Action BhBackStep::Behavior(const int myID) {
	return EnemyManager::Access(myID)->BackStep();
}