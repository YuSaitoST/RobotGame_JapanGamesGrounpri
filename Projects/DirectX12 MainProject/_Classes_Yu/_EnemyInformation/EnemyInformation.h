#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#define EnemyInfo EnemyInformation::GetInctance()

using namespace DirectX::SimpleMath;

class EnemyInformation {
public:
	static EnemyInformation& GetInctance() {
		static EnemyInformation inctance;
		return inctance;
	}

	void Push(Vector3 position, int& listID);
	void UpdatePosition(Vector3 position, const int id);
	void Erase(const int id);
	Vector3 ShortestDistanceTo(const Vector3 playerPos);

private:
	EnemyInformation() {}
	virtual ~EnemyInformation() {}

	std::vector<Vector3> posList_;
};