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

	// �s�����I������܂ŁA���t���[���J��Ԃ�
	if (lastAction_ == Action::REPEAT) {
		lastAction_ = lastNode_->Behavior(myID);
		enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));

		// �s�����I�������Ȃ烊�Z�b�g����
		if (lastAction_ != Action::REPEAT) {
			lastAction_ = Action::FAILIRE;
			lastNode_ = nullptr;
		}

		return lastAction_;
	}

	const float distance = PlayerInfo.GetDistance(enemy->myPosition());

	// ���g���U�����Ă��Ȃ��ꍇ
	if (enemy->nowAttackAttate() == AttackState::None_Attack) {
		const bool TooClose = distance <= ENParams.UNAPPROACHABLE_DISTANCE;
		const bool WithinShootingDistance = ENParams.ALWAYS_KEEP_DISTANCE_OPEN < distance&& distance < ENParams.RANGE_OF_SHOOTING;

		if (TooClose) {
			// Player�Ƃ̋������߂�����Ȃ�ABackStep�ŗ����
			lastAction_ = NewActToBeTaken(nd_backStep_)->Behavior(myID);
			enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));
		}
		else if (WithinShootingDistance) {
			// �˒��������Ȃ�ASideStep�Ŗ|�M������
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
			// �˒��������������Ȃ�ړ�����
			lastAction_ = NewActToBeTaken(nd_move_)->Behavior(myID);
		}
		else if (MiddleDistance) {
			if (randomDist_(randomEngine_) % 100 < PROBABILITY_OF_NOT_STEP[enemy->myLevel()]) {
				// �������Ȃ�m����SideStep�Ŗ|�M������
				lastAction_ = NewActToBeTaken(nd_sideStep_)->Behavior(myID);
			}
		}
		else if (DistanceThatCantBeAnyCloser && DistanceToInitiateMeleeAttack) {
			// �ߐڍU���͈͓��Ȃ牽�����Ȃ�
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
//	// �O��̍s�����I�����Ă���Ȃ�
//	if (lastAction_ != Action::REPEAT) {
//		// Lv.0�́A�U���ƈړ��𓯎��ɍs���Ȃ�
//		if (enemy->myLevel() == 0) {
//			// �U�����Ȃ�ړ����Ȃ�
//			if (enemy->nowAttackAttate() != AttackState::None_Attack)
//				return Action::FAILIRE;
//		}
//	}
//
//	const float distance = PlayerInfo.GetDistance(enemy->myPosition());
//	const bool near_close = distance < ENParams.MELEEATTACK_TO_DISTANCE;
//
//	// �������߂�����ꍇ�͊m���ŋ������J����(�ߐڒ��͂��Ȃ�)
//	if (enemy->nowAttackAttate() != AttackState::Adjacent) {
//		if (randomDist_(randomEngine_) % 100 < PROBABILITY_OF_NOT_STEP[enemy->myLevel()]) {
//			if (near_close) {
//				lastAction_ = nd_backStep_->Behavior(myID);
//				lastNode_ = nd_backStep_;
//			}
//		}
//	}
//
//	// �s�����I������܂ŁA���t���[���J��Ԃ�
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
//		//	// �U�����Ă��Ȃ����U���͈͓��Ȃ�ړ�����
//
//		//}
//		lastAction_ = nd_move_->Behavior(myID);
//		lastNode_ = nd_move_;
//	}
//	else if (nearDistance) {
//		// �U�������ߐڐ퓬�͈͓��Ƀv���C���[������Ȃ�A�ړ����邩�ǂ����m���Ŕ��f����
//		if (randomDist_(randomEngine_) % 100 < PROBABILITY_OF_NOT_STEP[enemy->myLevel()])
//			return Action::FAILIRE;
//
//		lastAction_ = nd_backStep_->Behavior(myID);
//		lastNode_ = nd_backStep_;
//	}
//	else  // �U�������ߐڐ퓬�͈͊O
//		lastAction_ = Action::FAILIRE;
//
//	return lastAction_;
//}