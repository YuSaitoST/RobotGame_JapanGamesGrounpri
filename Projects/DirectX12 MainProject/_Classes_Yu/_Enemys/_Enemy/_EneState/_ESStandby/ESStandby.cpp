#include "ESStandby.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"
#include "_Classes_Yu/_EnePosList/EnePosList.h"

void ESStandby::Initialize(const int myID) {
	enemy_		= EnemyManager::Access(myID);
	positionID_ = std::max((myID - 1), 0) % 3;
}

void ESStandby::Update(const int myID) {
	if (enemy_->myLevel() == 0) {
		SertchUnit();
	}
	else {
		UpperUnit();
	}

	if (PlayerInfo.GetDistance(enemy_->myPosition()) <= ENParams.DISTANCE_TO_NOTICE_PLAYER) {
		enemy_->SwitchState(FIGHTING);
	}
}

void ESStandby::SertchUnit() {
	// モブMSの行動、動きまわる

	enemy_->Move(DIRECTION[(int)isMoveRight_]);

	if (ENParams.MOB_RIGHT_END[positionID_] <= enemy_->myPosition().x) {
		isMoveRight_ = false;
	}
	else if (enemy_->myPosition().x <= ENParams.MOB_LEFT_END[positionID_]) {
		isMoveRight_ = true;
	}
}

void ESStandby::UpperUnit() {
	// ボスMSの行動、何もしない
}