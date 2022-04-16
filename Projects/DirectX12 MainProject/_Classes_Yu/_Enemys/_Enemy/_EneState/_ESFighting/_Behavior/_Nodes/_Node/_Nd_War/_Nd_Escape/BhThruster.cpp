#include "BhThruster.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhThruster::BhThruster() {

}

BhThruster::~BhThruster() {

}

Action BhThruster::Behavior(const int myID) {
	return EnemyManager::Access(myID)->Thruster();
}