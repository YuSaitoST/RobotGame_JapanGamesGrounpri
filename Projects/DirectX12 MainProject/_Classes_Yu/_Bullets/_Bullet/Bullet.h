#pragma once

#include "_Classes_Yu/_CellList/_Object/ObjectBase.h"

class Bullet final : public ObjectBase {
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

	inline bool IsBeenShot() const { return isShot_; }

	void Shoot(int ownerID, Vector3 pos, float rotY);

private:
	void SetFlyForward();

	bool isShot_;
};