#pragma once

#include "_Classes_Yu/_CellList/_Object/ObjectBase.h"
#include "_EneState/EneState.h"

#include "_EneState/_ESSpone/ESSpone.h"
#include "_EneState/_ESStandby/ESStandby.h"
#include "_EneState/_ESFighting/ESFighting.h"
#include "_Classes_Yu/_DeltaTime/DeltaTime.h"

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

	void Rotate(const float radian);
	Action Move(Vector3 forward);
	Action Thruster();
	Action BackStep();
	Action Adjacent();
	Action Shooting();

private:
	EneState* state_;
	ESSpone st_spone_;
	ESStandby st_standby_;
	ESFighting st_fighting_;
	bool isHitPlayer_;

	float timeDelta_;
	float jumpTime_;

	const float GRAVITY = 9.80665f;
};