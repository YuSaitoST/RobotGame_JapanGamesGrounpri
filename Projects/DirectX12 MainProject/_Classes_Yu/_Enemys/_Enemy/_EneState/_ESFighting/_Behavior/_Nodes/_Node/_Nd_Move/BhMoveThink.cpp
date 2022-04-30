#include "BhMoveThink.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/_Nd_War/_Nd_Escape/BhBackStep.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/_Node/_Nd_War/_Nd_Escape/BhSideStep.h"

BhMoveThink::BhMoveThink() {
	nd_move_		= new BhMove();
	nd_backStep_	= new BhRandSelector(new BhBackStep(), new BhSideStep());
	lastNode_		= nullptr;
	lastAction_		= Action::FAILIRE;

	std::random_device seed;
	randomEngine_	= std::mt19937(seed());
	randomDist_		= std::uniform_int_distribution<>(0, 99);
}

BhMoveThink::~BhMoveThink() {
	delete nd_backStep_;
	delete nd_move_;
}

Action BhMoveThink::Behavior(const int myID) {
	Enemy* enemy = EnemyManager::Access(myID);

	// 前回の行動が終了しているなら
	if (lastAction_ != Action::REPEAT) {
		// Lv.0は、攻撃と移動を同時に行えない
		if (enemy->myLevel() == 0) {
			// 攻撃中なら移動しない
			if (enemy->nowAttackAttate() != AttackState::None_Attack)
				return Action::FAILIRE;
		}
	}

	// 行動を終了するまで、毎フレーム繰り返す
	if (lastAction_ == Action::REPEAT) {
		lastAction_ = lastNode_->Behavior(myID);
		
		if (lastAction_ != Action::REPEAT) {
			lastAction_ = Action::FAILIRE;
			lastNode_ = nullptr;
		}

		return lastAction_;
	}

	const float distance = PlayerInfo.GetDistance(enemy->myPosition());
	const bool proximity_in_range = (distance <= ENParams.MELEEATTACK_TO_DISTANCE);
	const bool shooting_in_range = (ENParams.SHORTEST_DISTANCE <= distance) && (distance <= ENParams.DISTANCE_APPROACHING_PLAYER);
	const bool nearDistance = (distance < ENParams.SHORTEST_DISTANCE);

	// 攻撃していないなら移動
	if (enemy->nowAttackAttate() == AttackState::None_Attack) {
		if (proximity_in_range) {
			lastAction_ = Action::FAILIRE;
			lastNode_ = nullptr;
		}
		else if (shooting_in_range) {
			lastAction_ = nd_move_->Behavior(myID);
			lastNode_ = nd_move_;
		}
	}
	else if (nearDistance) {
		if (randomDist_(randomEngine_) % 100 < PROBABILITY_OF_NOT_STEP[enemy->myLevel()])
			return Action::FAILIRE;

		lastAction_ = nd_backStep_->Behavior(myID);
		lastNode_ = nd_backStep_;
	}
	else
		lastAction_ = Action::FAILIRE;

	return lastAction_;
}