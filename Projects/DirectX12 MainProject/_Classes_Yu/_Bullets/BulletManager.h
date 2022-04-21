#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

class Bullet;

class BulletManager {
public:
	BulletManager();
	virtual ~BulletManager() {}

	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

	static void Shooting(int ownerID, Vector3 pos, Vector3 forward, float rotY);

private:
	DX9::MODEL model_;  // ’eƒ‚ƒfƒ‹
	static std::vector<Bullet*> bulletList_;
};