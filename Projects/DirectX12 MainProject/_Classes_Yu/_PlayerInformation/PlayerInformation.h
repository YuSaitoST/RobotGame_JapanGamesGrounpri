#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes_Ao/PlayerManager/PlayerBase/PlayerBase.h"

#define PlayerInfo PlayerInformation

using namespace DirectX::SimpleMath;

class PlayerInformation {
public:
	PlayerInformation() {}
	virtual ~PlayerInformation() {}

	static AttackState NowAttackState() { return AttackState::None_Attack; }
	static Vector3 GetDirection(Vector3 myPos) { return VectorNomalized(GetPosition() - myPos); }
	static float GetDistance(Vector3 myPos) { return std::fabsf((GetPosition() - myPos).Length()); }

private:
	static Vector3 GetPosition() { return Vector3::Zero; }
	static Vector3 VectorNomalized(Vector3 vec) { vec.Normalize(); return vec; }
};