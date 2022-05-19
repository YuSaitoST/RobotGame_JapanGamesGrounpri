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

	enemy->HitCheck();

	//// �퓬�͈͊O�Ȃ�A�ҋ@��Ԃɐ؂�ւ���
	//if (ENParams.DISTANCE_TO_NOTICE_PLAYER <= PlayerInfo.GetDistance(enemy->myPosition())) {
	//	EnemyManager::RemoveEnePosList(enemy->myObjectID());
	//	enemy->SwitchState(ENE_STATE::STANDBY);
	//}
}