#include "ESStan.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"
#include "_Classes_Yu/_DeltaTime/DeltaTime.h"

ESStan::ESStan() {
	timer_ = new OriTimer(3.0f);
}

ESStan::~ESStan() {
	delete timer_;
}

void ESStan::Update(const int myID) {
	Enemy* enemy = EnemyManager::Access(myID);
	enemy->HitCheck();
	timer_->Update(DeltaTime::dt());

	if (timer_->TimeOut())
		enemy->SwitchState(ENE_STATE::FIGHTING);
}