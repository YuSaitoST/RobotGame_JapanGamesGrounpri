#include "EnePosList.h"

EnePosList::~EnePosList() {
	posList_.clear();
}

void EnePosList::SetPosition(const int id, DirectX::SimpleMath::Vector3* position) {
	posList_.emplace(id, position);
}

void EnePosList::ErasePosition(const int id) {
	posList_.erase(id);
}

Vector3 EnePosList::GetClosestCoordinate(const Vector3 position) {
	Vector3 targetPosition = Vector3::Zero;
	float minDistance = 99.0f;
	for (auto it = posList_.begin(); it != posList_.end(); ++it) {
		const float distance = Distance2Vector(Vector2(position.x, position.z), Vector2(it->second->x, it->second->z));
		if (distance < minDistance) {
			minDistance = distance;
			targetPosition = *it->second;
		}
	}
	return targetPosition;
}

float EnePosList::Distance2Vector(const Vector2 p1, const Vector2 p2) {
	return std::sqrtf(std::powf(p1.x - p2.x, 2) + std::powf(p1.y - p2.y, 2));
}