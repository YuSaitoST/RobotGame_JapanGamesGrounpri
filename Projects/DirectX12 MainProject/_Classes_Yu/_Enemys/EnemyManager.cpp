#include "EnemyManager.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EneStandardParamsLoad/EneStandardParamsLoad.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EneLvParamsLoad/EneLvParamsLoad.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EnesPositionLoad/EnesPositionLoad.h"

std::vector<Enemy*> EnemyManager::enemyList_;

EnemyManager::EnemyManager(const int enemyNum) {
	EneStandardParamsLoad::GetInstance().LoadParams();
	EneLvParamsLoad::GetInstance().LoadParams();
	EnesPositionLoad::GetInstance().LoadParams();

	assert(enemyNum == (LV1 + LV2 + LV3));

	enemyList_.reserve(enemyNum);

	for (int _i = 0; _i < LEVELS_NUM::LV1; ++_i)
		enemyList_.push_back(new Enemy((int)LEVELS::ONE, ENPos.GetPosition(_i), 1.0f));
	for (int _i = LEVELS_NUM::LV1; _i < LEVELS_NUM::LV1 + LEVELS_NUM::LV2; ++_i)
		enemyList_.push_back(new Enemy((int)LEVELS::TWO, ENPos.GetPosition(_i), 1.0f));
	for (int _i = LEVELS_NUM::LV1 + LEVELS_NUM::LV2; _i < enemyNum; ++_i)
		enemyList_.push_back(new Enemy((int)LEVELS::THREE, ENPos.GetPosition(_i), 1.0f));

	//for (int _i = 0; _i < enemyNum; ++_i)
	//	enemyList_.push_back(new Enemy((int)LEVELS::ONE, ENPos.GetPosition(_i), 1.0f));
}

EnemyManager::~EnemyManager() {
	for (int _i = enemyList_.size() - 1; 0 <= _i; --_i)
		delete enemyList_[_i];
}

Enemy* EnemyManager::Access(const int index) {
	return enemyList_[index];
}

void EnemyManager::Initialize() {
	for (int _i = 0; _i < enemyList_.size(); ++_i)
		enemyList_[_i]->Initialize(_i);
}

void EnemyManager::LoadAssets() {
	for (int _i = 0; _i < enemyList_.size(); ++_i)
		enemyList_[_i]->LoadAssets(L"Player\\SwordManEX\\armor_red2_0210b.X");
}

void EnemyManager::Update(const float deltaTime) {
	for (Enemy* enemy : enemyList_)
		enemy->Update(deltaTime);
}

void EnemyManager::Render() {
	for (Enemy* enemy : enemyList_)
		enemy->Render();
}