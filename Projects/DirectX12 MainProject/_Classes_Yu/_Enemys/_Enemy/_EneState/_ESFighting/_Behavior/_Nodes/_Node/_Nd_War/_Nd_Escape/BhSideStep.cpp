#include "BhSideStep.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhSideStep::BhSideStep() {
	std::random_device seed;
	randomEngine = std::mt19937(seed());
	randomDist = std::uniform_int_distribution<>(0, 1);
}

Action BhSideStep::Behavior(const int myID) {
	Enemy* enemy = EnemyManager::Access(myID);
	const int sign = 2 * randomDist(randomEngine) - 1;
	return enemy->SideStep(PlayerInfo.GetDirection(sign * enemy->myPosition()));
}