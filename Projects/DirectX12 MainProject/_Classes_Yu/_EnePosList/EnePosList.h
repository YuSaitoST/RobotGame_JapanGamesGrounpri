#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

class EnePosList {
public:
	virtual ~EnePosList();
	void SetPosition(const int id, Vector3* position);
	void ErasePosition(const int id);
	Vector3 GetClosestCoordinate(const Vector3 position);

private:
	float Distance2Vector(const Vector2 p1, const Vector2 p2);

	std::unordered_map<int, Vector3*> posList_;
};