#include "BhMoveThink.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

BhMoveThink::BhMoveThink() {
	nd_move_		= new BhMove();
	nd_backStep_	= new BhBackStep();
	nd_sideStep_	= new BhSideStep();
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

	// 行動を終了するまで、毎フレーム繰り返す
	if (lastAction_ == Action::REPEAT) {
		lastAction_ = lastNode_->Behavior(myID);
		enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));

		// 行動が終了したならリセットする
		if (lastAction_ != Action::REPEAT) {
			lastAction_ = Action::FAILIRE;
			lastNode_ = nullptr;
		}

		return lastAction_;
	}

	const float distance = PlayerInfo.GetDistance(enemy->myPosition());

	// 自身が攻撃していない場合
	if (enemy->nowAttackAttate() == AttackState::None_Attack) {
		const bool TooClose = distance <= ENParams.UNAPPROACHABLE_DISTANCE;
		const bool WithinShootingDistance = ENParams.ALWAYS_KEEP_DISTANCE_OPEN < distance&& distance < ENParams.RANGE_OF_SHOOTING;

		if (TooClose) {
			// Playerとの距離が近すぎるなら、BackStepで離れる
			lastAction_ = NewActToBeTaken(nd_backStep_)->Behavior(myID);
			enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));
		}
		else if (WithinShootingDistance) {
			// 射程距離内なら、SideStepで翻弄させる
			lastAction_ = NewActToBeTaken(nd_sideStep_)->Behavior(myID);
			enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));
		}
		else {
			lastAction_ = NewActToBeTaken(nd_backStep_)->Behavior(myID);
		}
	}
	else {
		const bool FartherThanTheShootingRange = ENParams.RANGE_OF_SHOOTING < distance;
		const bool MiddleDistance = ENParams.RANGE_OF_MELEEATTACK < distance&& distance < ENParams.ALWAYS_KEEP_DISTANCE_OPEN;
		const bool DistanceToInitiateMeleeAttack = distance <= ENParams.RANGE_OF_MELEEATTACK;
		const bool DistanceThatCantBeAnyCloser = ENParams.UNAPPROACHABLE_DISTANCE < distance;

		if (FartherThanTheShootingRange) {
			// 射程距離よりも遠いなら移動する
			lastAction_ = NewActToBeTaken(nd_move_)->Behavior(myID);
		}
		else if (MiddleDistance) {
			if (randomDist_(randomEngine_) % 100 < PROBABILITY_OF_NOT_STEP[enemy->myLevel()]) {
				// 中距離なら確立でSideStepで翻弄させる
				lastAction_ = NewActToBeTaken(nd_sideStep_)->Behavior(myID);
			}
		}
		else if (DistanceThatCantBeAnyCloser && DistanceToInitiateMeleeAttack) {
			// 近接攻撃範囲内なら何もしない
			return FAILIRE;
		}
		else {
			return FAILIRE;
		}
	}

	return lastAction_;
}

Node* BhMoveThink::NewActToBeTaken(Node* node) {
	lastNode_ = node;
	return lastNode_;
}

//Action BhMoveThink::Behavior(const int myID) {
//	Enemy* enemy = EnemyManager::Access(myID);
//
//	// 前回の行動が終了しているなら
//	if (lastAction_ != Action::REPEAT) {
//		// Lv.0は、攻撃と移動を同時に行えない
//		if (enemy->myLevel() == 0) {
//			// 攻撃中なら移動しない
//			if (enemy->nowAttackAttate() != AttackState::None_Attack)
//				return Action::FAILIRE;
//		}
//	}
//
//	const float distance = PlayerInfo.GetDistance(enemy->myPosition());
//	const bool near_close = distance < ENParams.MELEEATTACK_TO_DISTANCE;
//
//	// 距離が近すぎる場合は確立で距離を開ける(近接中はやらない)
//	if (enemy->nowAttackAttate() != AttackState::Adjacent) {
//		if (randomDist_(randomEngine_) % 100 < PROBABILITY_OF_NOT_STEP[enemy->myLevel()]) {
//			if (near_close) {
//				lastAction_ = nd_backStep_->Behavior(myID);
//				lastNode_ = nd_backStep_;
//			}
//		}
//	}
//
//	// 行動を終了するまで、毎フレーム繰り返す
//	if (lastAction_ == Action::REPEAT) {
//		lastAction_ = lastNode_->Behavior(myID);
//		
//		if (lastAction_ != Action::REPEAT) {
//			lastAction_ = Action::FAILIRE;
//			lastNode_ = nullptr;
//		}
//
//		return lastAction_;
//	}
//
//	const bool shooting_in_range = (ENParams.SHORTEST_DISTANCE <= distance) && (distance <= ENParams.DISTANCE_APPROACHING_PLAYER);
//	const bool proximity_in_range = !near_close && (distance <= ENParams.MELEEATTACK_TO_DISTANCE);
//	const bool nearDistance = !near_close && (distance < ENParams.SHORTEST_DISTANCE);
//
//	if (enemy->nowAttackAttate() == AttackState::None_Attack) {
//		//if (proximity_in_range || shooting_in_range) {
//		//	// 攻撃していない且つ攻撃範囲内なら移動する
//
//		//}
//		lastAction_ = nd_move_->Behavior(myID);
//		lastNode_ = nd_move_;
//	}
//	else if (nearDistance) {
//		// 攻撃中且つ近接戦闘範囲内にプレイヤーがいるなら、移動するかどうか確率で判断する
//		if (randomDist_(randomEngine_) % 100 < PROBABILITY_OF_NOT_STEP[enemy->myLevel()])
//			return Action::FAILIRE;
//
//		lastAction_ = nd_backStep_->Behavior(myID);
//		lastNode_ = nd_backStep_;
//	}
//	else  // 攻撃中且つ近接戦闘範囲外
//		lastAction_ = Action::FAILIRE;
//
//	return lastAction_;
//}