#include "ESStandby.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"
#include "_Classes_Yu/_EnemyInformation/EnemyInformation.h"

void ESStandby::Initialize(const int myID) {
	enemy_ = EnemyManager::Access(myID);
	positionID_ = std::max((myID - 1), 0) % 3;
}

void ESStandby::Update(const int myID) {
	if (enemy_->myLevel() == 0)
		SertchUnit();
	else
		UpperUnit();

	if (PlayerInfo.GetDistance(enemy_->myPosition()) <= ENParams.DISTANCE_APPROACHING_PLAYER) {
		EnemyInfo.Push(enemy_->myPosition(), enemy_->GetPosListID());
		enemy_->SwitchState(FIGHTING);
	}
}

void ESStandby::SertchUnit() {
	if (isMoveRight_)
		enemy_->Move(Vector3::Right);
	else
		enemy_->Move(Vector3::Left);

	if (ENParams.MOB_RIGHT_END[positionID_] <= enemy_->myPosition().x)
		isMoveRight_ = false;
	else if (enemy_->myPosition().x <= ENParams.MOB_LEFT_END[positionID_])
		isMoveRight_ = true;
}

void ESStandby::UpperUnit() {

}