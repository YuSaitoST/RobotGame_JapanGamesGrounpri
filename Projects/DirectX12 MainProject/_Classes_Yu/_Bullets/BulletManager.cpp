#include "BulletManager.h"
#include "_Bullet/Bullet.h"

std::vector<Bullet*> BulletManager::bulletList_;

BulletManager::BulletManager() {
	bulletList_.reserve(10);

	for (int _i = 0; _i < 10; ++_i)
		bulletList_.push_back(new Bullet());
}

void BulletManager::LoadAssets() {
	model_ = DX9::Model::CreateSphere(DXTK->Device9, 0.05f, 10, 10);
}

void BulletManager::Update(const float deltaTime) {
	for (Bullet* bt : bulletList_)
		if (bt->IsBeenAttack())
			bt->Update(deltaTime);
}

void BulletManager::Render() {
	for (Bullet* bt : bulletList_)
		if (bt->IsBeenAttack())
			bt->Render(model_);
}

void BulletManager::Shooting(int ownerID, int damage, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 forward, float rotY) {
	bool completion = false;
	for (Bullet* bt : bulletList_) {
		if (!bt->IsBeenAttack()) {
			bt->Shoot(ownerID, damage, pos, forward, rotY);
			completion = true;
			break;
		}
	}

	if (!completion) {
		bulletList_.push_back(new Bullet());
		bulletList_.back()->Shoot(ownerID, damage, pos, forward, rotY);
	}
}