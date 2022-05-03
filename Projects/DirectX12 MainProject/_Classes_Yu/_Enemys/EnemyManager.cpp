#include "EnemyManager.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EneStandardParamsLoad/EneStandardParamsLoad.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EneLvParamsLoad/EneLvParamsLoad.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EnesPositionLoad/EnesPositionLoad.h"

std::vector<Enemy*> EnemyManager::enemyList_;

EnemyManager::EnemyManager() {
	EneStandardParamsLoad::GetInstance().LoadParams();
	EneLvParamsLoad::GetInstance().LoadParams();
	EnesPositionLoad::GetInstance().LoadParams();

	enemyList_.reserve(LV1 + LV2 - 1);

	for (int _i = 0; _i < LEVELS_NUM::LV1; ++_i)
		enemyList_.push_back(new Enemy((int)LEVELS::ONE, ENPos.GetPosition(_i), 1.0f));
}

EnemyManager::~EnemyManager() {
	for (int _i = enemyList_.size() - 1; 0 <= _i; --_i)
		delete enemyList_[_i];
}

Enemy* EnemyManager::Access(const int index) {
	return enemyList_[index - 1];
}

void EnemyManager::Initialize() {
	for (int _i = 0; _i < enemyList_.size(); ++_i)
		enemyList_[_i]->Initialize(_i + 1);
}

void EnemyManager::LoadAssets() {
	for (int _i = 0; _i < enemyList_.size(); ++_i)
		enemyList_[_i]->LoadAssets(L"Player\\j_mein.x");
}

void EnemyManager::Update(const float deltaTime) {
	for (Enemy* enemy : enemyList_)
		enemy->Update(deltaTime);
}

void EnemyManager::Render() {
	for (Enemy* enemy : enemyList_)
		enemy->Render();
}