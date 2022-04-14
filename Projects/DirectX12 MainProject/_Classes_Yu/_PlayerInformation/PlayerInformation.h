#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes_Yu/_CellList/_Object/AttackState.h"

#define PlayerInfo PlayerInformation::GetInctance()

using namespace DirectX::SimpleMath;

class PlayerInformation {
public:
	static PlayerInformation& GetInctance() {
		static PlayerInformation inctance;
		return inctance;
	}

	void SetMenber(Vector3* pos, AttackState* ATstate) { position_ = pos; attackState_ = ATstate; }
	void SetMenber(Vector3* pos) { position_ = pos; }
	Vector3* GetPositionPointer() const { return position_; }

	//AttackState NowAttackState() { return *attackState_; }
	AttackState NowAttackState() { return AttackState::None_Attack; }
	Vector3 GetDirection(Vector3 myPos) { return VectorNomalized(*GetPosition() - myPos); }
	float GetDistance(Vector3 myPos) { return std::fabsf((*GetPosition() - myPos).Length()); }

private:
	PlayerInformation() {}
	virtual ~PlayerInformation() {}

	Vector3* GetPosition() { return position_; }
	Vector3 VectorNomalized(Vector3 vec) { vec.Normalize(); return vec; }

	Vector3*		position_;
	AttackState*	attackState_;
};