#pragma once

#include <vector>
#include "_Classes_Yu/_Enemys/_Enemy/Enemy.h"

class EnemyManager {
public:
	EnemyManager(const int enemyNum);
	virtual ~EnemyManager();

	void PushList(Vector3 position, float r);
	static Enemy* Access(const int index);

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

private:
	static std::vector<Enemy*> enemyList_;
	DX9::SKINNEDMODEL model_;
};
