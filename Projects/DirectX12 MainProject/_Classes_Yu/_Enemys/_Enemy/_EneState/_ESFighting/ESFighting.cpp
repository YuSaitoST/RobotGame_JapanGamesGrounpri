#include "ESFighting.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

ESFighting::ESFighting() {
	root_ = new Root();
}

ESFighting::~ESFighting() {
	delete root_;
}

void ESFighting::Update(const int myID) {
	root_->Update(myID);

	EnemyManager::Access(myID)->HitCheck();
}