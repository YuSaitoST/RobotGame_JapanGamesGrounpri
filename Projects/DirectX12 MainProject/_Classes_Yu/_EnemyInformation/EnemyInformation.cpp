#include "EnemyInformation.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

void EnemyInformation::Push(Vector3 position, int& listIndex) {
	posList_.push_back(position);
	posList_.push_back(position);
	listIndex = posList_.size() - 1;
}

void EnemyInformation::UpdatePosition(Vector3 position, const int id) {
	posList_.at(id) = position;
}

void EnemyInformation::Erase(const int id) {
	posList_.erase(posList_.begin() + id);
}

Vector3 EnemyInformation::ShortestDistanceTo(const Vector3 playerPos) {
	int enemyID = -1;
	float minDistance = 99;
	float distance = 0;
	for (int _i = 0; _i < posList_.size(); ++_i) {
		distance = std::fabsf((playerPos - posList_.at(_i)).Length());
		if (distance < minDistance) {
			enemyID = _i;
			break;
		}
		minDistance = distance;
	}
	return posList_.at(enemyID);
}