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

	// 行動を終了するまで、同じ行動を繰り返す
	if (lastAction_ == Action::REPEAT) {
		lastAction_ = lastNode_->Behavior(myID);
		enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));

		// 行動が終了したならリセットする
		if (lastAction_ != Action::REPEAT) {
			lastAction_ = Action::FAILIRE;
		}

		return lastAction_;
	}

	lastAction_ = NewActToBeTaken(ActThinks(enemy))->Behavior(myID);

	return lastAction_;
}

Node* BhMoveThink::ActThinks(Enemy* enemy) {
	const float distance					= PlayerInfo.GetDistance(enemy->myPosition());
	const bool TooClose						= distance <= ENParams.UNAPPROACHABLE_DISTANCE;
	const bool FartherThanTheShootingRange	= ENParams.RANGE_OF_SHOOTING < distance;

	if (FartherThanTheShootingRange) {
		// 射程距離よりも遠いなら移動する
		return nd_move_;
	}
	else if (TooClose) {
		// Playerとの距離が近すぎるなら、BackStepで離れる
		enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));
		return nd_backStep_;
	}
	
	// 自身が攻撃していない場合
	if (enemy->nowAttackAttate() == AttackState::None_Attack) {
		const bool WithinShootingDistance = ENParams.ALWAYS_KEEP_DISTANCE_OPEN < distance&& distance < ENParams.RANGE_OF_SHOOTING;
		if (WithinShootingDistance) {
			// 射程距離内なら、SideStepで翻弄させる
			enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));
			return nd_sideStep_;
		}
		else {
			return nd_move_;
		}
	}
	else {
		const bool MiddleDistance					= ENParams.RANGE_OF_MELEEATTACK < distance&& distance < ENParams.ALWAYS_KEEP_DISTANCE_OPEN;
		const bool DistanceToInitiateMeleeAttack	= distance <= ENParams.RANGE_OF_MELEEATTACK;
		const bool DistanceThatCantBeAnyCloser		= ENParams.UNAPPROACHABLE_DISTANCE < distance;

		if (MiddleDistance) {
			if (PROBABILITY_OF_STEP[enemy->myLevel()] < randomDist_(randomEngine_) % 100) {
				// 中距離なら確立でSideStepで翻弄させる
				return nd_sideStep_;
			}
		}
		//else if (DistanceThatCantBeAnyCloser && DistanceToInitiateMeleeAttack) {
		//	// 近接攻撃範囲内なら何もしない
		//	return nullptr;
		//}
		else {
			return nullptr;
		}
	}
}

Node* BhMoveThink::NewActToBeTaken(Node* node) {
	// 行動の更新
	if (node != nullptr) {
		lastNode_ = node;
	}
	return lastNode_;
}