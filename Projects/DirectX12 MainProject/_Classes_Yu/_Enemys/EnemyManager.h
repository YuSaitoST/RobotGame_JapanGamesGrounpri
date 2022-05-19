#pragma once

#include <vector>
#include "_Classes_Yu/_Enemys/_Enemy/Enemy.h"
#include "_Classes_Yu/_EnePosList/EnePosList.h"

enum LEVELS_NUM { LV1 = 1, LV2 = 0 };

class EnemyManager {
public:
	EnemyManager();
	virtual ~EnemyManager();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

	static Enemy* Access(const int index);
	static Vector3 GetClosestCoordinate(const Vector3 position) { enePosList_->GetClosestCoordinate(position); }
	static bool DoesThisIDexist(const int id) { return enePosList_->DoesThisIDexist(id); }
	static void RemoveEnePosList(const int id) { enePosList_->ErasePosition(id); }

private:
	static std::vector<Enemy*> enemyList_;
	static EnePosList* enePosList_;
};
