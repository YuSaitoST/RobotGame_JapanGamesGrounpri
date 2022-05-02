#include "ESFighting.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"
#include "_Classes_Yu/_EnemyInformation/EnemyInformation.h"

ESFighting::ESFighting() {
	root_ = new Root();
}

ESFighting::~ESFighting() {
	delete root_;
}

void ESFighting::Update(const int myID) {
	root_->Update(myID);

	Enemy* enemy = EnemyManager::Access(myID);
	EnemyInfo.UpdatePosition(enemy->myPosition(), enemy->GetPosListID());

	enemy->HitCheck();
}