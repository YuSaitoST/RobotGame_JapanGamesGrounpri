#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class Bullet;

class BulletManager {
public:
	BulletManager();
	virtual ~BulletManager() {}

	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

	static void Shooting(int ownerID, DirectX::SimpleMath::Vector3 pos, float rotY);

private:
	DX9::MODEL model_;  // ’eƒ‚ƒfƒ‹
	static std::vector<Bullet*> bulletList_;
};