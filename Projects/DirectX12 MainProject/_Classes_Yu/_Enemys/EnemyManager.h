#pragma once

#include <vector>
#include "_Classes_Yu/_Enemys/_Enemy/Enemy.h"

class EnemyManager {
private:
	enum LEVELS_NUM { LV1 = 1, LV2 = 0 };

public:
	EnemyManager();
	virtual ~EnemyManager();

	static Enemy* Access(const int index);

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

private:
	static std::vector<Enemy*> enemyList_;
};
