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
	timer_->Update(DeltaTime::dt());

	if (timer_->TimeOut())
		EnemyManager::Access(myID)->SwitchState(ENE_STATE::FIGHTING);
}