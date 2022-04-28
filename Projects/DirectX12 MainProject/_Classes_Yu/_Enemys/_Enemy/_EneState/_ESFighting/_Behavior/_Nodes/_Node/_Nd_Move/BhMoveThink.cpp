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
	randomEngine_ = std::mt19937(seed());
	randomDist_ = std::uniform_int_distribution<>(0, 99);
}

BhMoveThink::~BhMoveThink() {
	delete nd_backStep_;
	delete nd_move_;
}

Action BhMoveThink::Behavior(const int myID) {
	Enemy* enemy = EnemyManager::Access(myID);

	if (lastAction_ != Action::REPEAT) {
		// Lv.0‚ÍAUŒ‚‚ÆˆÚ“®‚ð“¯Žž‚És‚¦‚È‚¢
		if (enemy->myLevel() == 0) {
			// UŒ‚’†‚È‚çˆÚ“®‚µ‚È‚¢
			if (enemy->nowAttackAttate() != AttackState::None_Attack)
				return Action::FAILIRE;
		}
	}

	if (lastAction_ == Action::REPEAT) {
		lastAction_ = lastNode_->Behavior(myID);
		
		if (lastAction_ != Action::REPEAT) {
			lastAction_ = Action::FAILIRE;
			lastNode_ = nullptr;
		}

		return lastAction_;
	}

	const float distance = PlayerInfo.GetDistance(enemy->myPosition());
	const bool certainDistance = (ENParams.SHORTEST_DISTANCE <= distance) && (distance <= ENParams.DISTANCE_APPROACHING_PLAYER);
	const bool nearDistance = (distance < ENParams.SHORTEST_DISTANCE);

	if (certainDistance) {
		// UŒ‚’†‚È‚çˆÚ“®‚µ‚È‚¢
		if (enemy->nowAttackAttate() != AttackState::None_Attack)
			return Action::FAILIRE;

		lastAction_ = nd_move_->Behavior(myID);
		lastNode_	= nd_move_;
	}
	else if (nearDistance) {
		if (randomDist_(randomEngine_) % 100 < PROBABILITY_OF_NOT_STEP[enemy->myLevel()])
			return Action::FAILIRE;

		lastAction_ = nd_backStep_->Behavior(myID);
		lastNode_	= nd_backStep_;
	}
	else
		lastAction_ = Action::FAILIRE;

	return lastAction_;
}