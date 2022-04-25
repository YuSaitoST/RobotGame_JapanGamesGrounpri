#pragma once

#include <vector>
#include "_Classes_Yu/_Enemys/_Enemy/Enemy.h"

class EnemyManager {
private:
	enum LEVELS_NUM { LV1 = 9, LV2 = 4, LV3 = 1 };

public:
	EnemyManager(const int enemyNum);
	virtual ~EnemyManager();

	static Enemy* Access(const int index);

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

private:
	static std::vector<Enemy*> enemyList_;
};
