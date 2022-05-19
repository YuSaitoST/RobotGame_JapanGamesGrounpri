#pragma once

#include "_Classes_Yu/_CellList/_Object/WeaponBase.h"

class MeleeWeapon final : public WeaponBase {
public:
	MeleeWeapon();
	virtual ~MeleeWeapon() {}

	virtual void Initialize(const int id);
	virtual void LoadAssets();
	virtual void LoadAssets(std::wstring file_name) {}
	virtual void Update(const float deltaTime) {}
	virtual void Render();
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender() {}

	void UpdatePosition(Vector3 position, Vector3 forward);

private:
	const Vector3 ADJUSTMENT = Vector3(0.8f, 0.0f, 0.8f);
	DX9::MODEL mod_;  // テスト用
};