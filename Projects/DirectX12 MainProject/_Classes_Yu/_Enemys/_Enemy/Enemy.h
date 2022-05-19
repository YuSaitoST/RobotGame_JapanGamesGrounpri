#pragma once

#include "_Classes_Yu/_CellList/_Object/ObjectBase.h"
#include "_Classes_Yu/_SoundPlayer/SoundPlayer.h"
#include "_Classes_Yu/_MSHP/MSHP.h"
#include "_Classes_Yu/_MSShoulderSide/MSShoulderSide.h"
#include "_EneState/EneState.h"
#include "_EneState/SwitchState.h"
#include "_Classes_Yu/_MeleeWeapon/MeleeWeapon.h"

enum Action;
class Enemy final : public ObjectBase {
public:
	Enemy(int level, Vector3 pos, float r);
	virtual ~Enemy();

	virtual void Initialize(const int id);
	virtual void LoadAssets() {};
	virtual void LoadAssets(std::wstring file_name);
	virtual void Update(const float deltaTime);
	virtual void Render();
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender() {};

	void SwitchState(ENE_STATE state);
	void HitCheck();
	void ResetAttackState() { attackState_ = AttackState::None_Attack; }

	Vector3* GetPosPointer() { return &pos_; }
	int myLevel() const { return level_; }
	int& GetPosListID() { return posListID_; }
	bool IsInAction() const { return isInStep_; }

	Action Move(const Vector3 targetDirection);
	Action Slide(const Vector3 moveDirection);
	Action BackStep();
	Action SideStep(const Vector3 targetDirection);
	Action Adjacent();
	Action Shooting();
	
	void Rotate(const Vector3 targetDirection);

private:
	void SetMember();

	const ENE_STATE STATE_OF_DAMAGE[2] = { ENE_STATE::STAN, ENE_STATE::DOWN };

	Action Step(const Vector3 moveDirection);

	HPGauge* hp_;
	OriTimer* actionInterval_;
	SoundPlayer* se_running_;
	SoundPlayer* se_adjacent_;
	SoundPlayer* se_shooting_;

	//MSShoulderSide* shoulderL_;

	EneState* state_;
	SwitchStates* m_state_;

	MeleeWeapon* meleeWapon_;

	//DX9::SKINNEDMODEL model_;
	DX9::MODEL model_;

	DX9::SHADER shader_;

	int posListID_;
	int level_;
	bool isInStep_;
	bool isHitPlayer_;

	float timeDelta_;
	float jumpTime_;

	Vector3 moveDirection_;
	Vector3 moveStartCoordinate_;

	Action lastAction_;

	const float GRAVITY = 9.8f;
};