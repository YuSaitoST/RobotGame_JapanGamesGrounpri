#pragma once

#include "_Classes_Yu/_CellList/_Object/WeaponBase.h"

class Bullet final : public WeaponBase {
public:
	Bullet();
	virtual ~Bullet() {}

	virtual void Initialize(const int id) {}
	virtual void LoadAssets() {}
	virtual void LoadAssets(std::wstring file_name) {}
	virtual void Update(const float deltaTime);
	virtual void Render() {}
	virtual void Render(DX9::MODEL& model);
	virtual void UIRender() {}

	void Shoot(int ownerID, int damage, Vector3 pos, Vector3 forward, float rotY);
};