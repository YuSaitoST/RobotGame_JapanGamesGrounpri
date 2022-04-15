#pragma once

#include "_Classes_Yu/_CellList/_Object/ObjectBase.h"
#include "_Classes_Yu/_SoundPlayer/SoundPlayer.h"
#include "_EneState/EneState.h"

#include "_EneState/_ESSpone/ESSpone.h"
#include "_EneState/_ESStandby/ESStandby.h"
#include "_EneState/_ESFighting/ESFighting.h"

enum Action;
class Enemy final : public ObjectBase {
public:
	Enemy();
	Enemy(Vector3 pos, float r);
	virtual ~Enemy();

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name) {}
	virtual void Update(const float deltaTime);
	virtual void Render() {}
	virtual void Render(DX9::SKINNEDMODEL& model);
	virtual void UIRender() {}

	void SwitchState(ENE_STATE state);

	Vector3* GetPosP() { return &pos_; }

	Action Move(const Vector3 targetDirection);
	Action Thruster();
	Action BackStep();
	Action SideStep(const Vector3 targetDirection);
	Action Adjacent();
	Action Shooting();

private:
	void Rotate(const Vector3 targetDirection);
	Action Step(const Vector3 moveDirection);

	SoundPlayer* se_adjacent_;
	SoundPlayer* se_shooting_;

	EneState* state_;
	ESSpone st_spone_;
	ESStandby st_standby_;
	ESFighting st_fighting_;
	bool isHitPlayer_;

	float timeDelta_;
	float jumpTime_;

	Vector3 moveDirection_;

	const float GRAVITY = 9.80665f;
	const std::wstring seNameAtk = L"_Sounds\\_SE\\_Attack\\SELab_useOnesSword1.wav";
	const std::wstring seNameBem = L"_Sounds\\_SE\\_Attack\\SELab_beamCannon1.wav";
};