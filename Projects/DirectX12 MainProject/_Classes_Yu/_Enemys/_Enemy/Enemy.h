#pragma once

#include "_Classes_Yu/_CellList/_Object/ObjectBase.h"
#include "_Classes_Yu/_SoundPlayer/SoundPlayer.h"
#include "_Classes_Yu/_HPGauge/HPGauge.h"
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

	Vector3* GetPosP() { return &pos_; }
	int myLevel() const { return level_; }
	int& GetPosListID() { return posListID_; }
	bool IsInAction() const { return isInStep_; }

	Action Move(const Vector3 targetDirection);
	Action Thruster();
	Action BackStep();
	Action SideStep(const Vector3 targetDirection);
	Action Adjacent();
	Action Shooting();

private:
	void SetMember();

	void Rotate(const Vector3 targetDirection);
	Action Step(const Vector3 moveDirection);
	Action Slide(const Vector3 moveDirection);

	HPGauge* hp_;
	OriTimer* actionInterval_;
	SoundPlayer* se_running_;
	SoundPlayer* se_adjacent_;
	SoundPlayer* se_shooting_;

	//MSShoulderSide* shoulderL_;

	EneState* state_;
	SwitchStates* m_state_;

	MeleeWeapon* meleeWapon_;

	DX9::SKINNEDMODEL model_;

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
	const std::wstring seNameRun = L"_Sounds\\_SE\\SELab_RunningOnAsphalt1.wav";
	const std::wstring seNameAtk = L"_Sounds\\_SE\\_Attack\\SELab_useOnesSword1.wav";
	const std::wstring seNameBem = L"_Sounds\\_SE\\_Attack\\SELab_beamCannon1.wav";
};