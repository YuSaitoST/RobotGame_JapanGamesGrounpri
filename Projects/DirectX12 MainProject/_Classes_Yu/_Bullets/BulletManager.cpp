#include "BulletManager.h"
#include "_Bullet/Bullet.h"

BulletManager::BulletManager() {
	bulletList_.reserve(10);

	for (int _i = 0; _i < 10; ++_i)
		bulletList_.push_back(new Bullet());
}

void BulletManager::LoadAssets() {
	model_ = DX9::Model::CreateSphere(DXTK->Device9, 0.5f, 10, 10);
}

void BulletManager::Update(const float deltaTime) {
	for (Bullet* bt : bulletList_)
		if (bt->IsBeenShot())
			bt->Update(deltaTime);
}

void BulletManager::Render() {
	for (Bullet* bt : bulletList_)
		if (bt->IsBeenShot())
			bt->Render(model_);
}  // ’eƒ‚ƒfƒ‹‚ÆAŽå‚É‘Î‰ž‚µ‚½texture‚ð“n‚·

void BulletManager::Shooting(int ownerID, DirectX::SimpleMath::Vector3 pos, float rotY) {
	bool completion = false;
	for (Bullet* bt : bulletList_) {
		if (!bt->IsBeenShot()) {
			bt->Shoot(ownerID, pos, rotY);
			completion = true;
			break;
		}
	}

	if (!completion) {
		bulletList_.push_back(new Bullet());
		bulletList_.back()->Shoot(ownerID, pos, rotY);
	}
}