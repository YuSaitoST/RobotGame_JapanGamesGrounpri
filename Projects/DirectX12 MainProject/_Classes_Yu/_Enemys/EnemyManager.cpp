#include "EnemyManager.h"

std::vector<Enemy*> EnemyManager::enemyList_;

EnemyManager::EnemyManager(const int enemyNum) {
	enemyList_.reserve(enemyNum);
}

EnemyManager::~EnemyManager() {
	for (int _i = enemyList_.size() - 1; 0 <= _i; --_i)
		delete enemyList_[_i];
}

void EnemyManager::PushList(Vector3 position, float r) {
	enemyList_.push_back(new Enemy(position, r));
}

Enemy* EnemyManager::Sertch(const int index) {
	return enemyList_[index];
}

void EnemyManager::Initialize() {
	for (int _i = 0; _i < enemyList_.size(); ++_i)
		enemyList_[_i]->Initialize(_i);
}

void EnemyManager::LoadAssets() {
	model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player\\SwordManEX\\armor_red2_0210b.X");
	model_->SetPosition(Vector3::Zero);
	model_->SetScale(0.1f);
}

void EnemyManager::Update(const float deltaTime) {
	for (Enemy* enemy : enemyList_)
		enemy->Update(deltaTime);
}

void EnemyManager::Render() {
	for (Enemy* enemy : enemyList_)
		enemy->Render(model_);
}