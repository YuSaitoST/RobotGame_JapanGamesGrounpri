#pragma once

#include "_Classes_Yu/_CellList/CellList.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"
#include "_Classes_Yu/_Bullets/BulletManager.h"
#include "_Classes_Yu/_EnesStronghold/EnesStronghold.h"

using namespace DirectX::SimpleMath;

extern CellList cellList;

class ObjectManager {
public:
	ObjectManager();
	virtual ~ObjectManager();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void RenderModels();
	void RenderSprites();

	static Enemy* GetEnemy(const int index) { return m_enemy_->Access(index); }
	static void SetShooting(int ownerID, int damage, Vector3 pos, Vector3 forward, float rotY) { BulletManager::Shooting(ownerID, damage, pos, forward, rotY); }

private:
	static EnemyManager* m_enemy_;
	BulletManager* m_bullet_;
	EnesStronghold* ensBase_;
};