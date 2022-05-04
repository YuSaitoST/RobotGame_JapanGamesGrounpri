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

	Enemy* enemy = EnemyManager::Access(myID);
	//EnemyInfo.UpdatePosition(enemy->myPosition(), enemy->GetPosListID());

	enemy->HitCheck();

	// �퓬�͈͊O�Ȃ�A�ҋ@��Ԃɐ؂�ւ���
	if (ENParams.DISTANCE_TO_NOTICE_PLAYER <= PlayerInfo.GetDistance(enemy->myPosition())) {
		//enemy->ErasePosList();
		enemy->SwitchState(ENE_STATE::STANDBY);
	}
}