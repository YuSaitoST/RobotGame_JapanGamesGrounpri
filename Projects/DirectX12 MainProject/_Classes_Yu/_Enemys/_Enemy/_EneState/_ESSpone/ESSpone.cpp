#include "ESSpone.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

void ESSpone::Update(const int myID) {
	EnemyManager::Sertch(myID)->SwitchState(STANDBY);
}