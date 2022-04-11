#pragma once

#include "_Classes_Yu/_CellList/_Object/ObjectBase.h"
#include "_EneState/EneState.h"

#include "_EneState/_ESSpone/ESSpone.h"
#include "_EneState/_ESStandby/ESStandby.h"
#include "_EneState/_ESFighting/ESFighting.h"

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
};