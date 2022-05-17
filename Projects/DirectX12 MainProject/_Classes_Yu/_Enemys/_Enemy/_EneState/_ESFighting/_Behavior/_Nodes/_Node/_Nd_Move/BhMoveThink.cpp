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

	// �s�����I������܂ŁA�����s�����J��Ԃ�
	if (lastAction_ == Action::REPEAT) {
		lastAction_ = lastNode_->Behavior(myID);
		enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));

		// �s�����I�������Ȃ烊�Z�b�g����
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
		// �˒��������������Ȃ�ړ�����
		return nd_move_;
	}
	else if (TooClose) {
		// Player�Ƃ̋������߂�����Ȃ�ABackStep�ŗ����
		enemy->Rotate(PlayerInfo.GetDirection(enemy->myPosition()));
		return nd_backStep_;
	}
	
	// ���g���U�����Ă��Ȃ��ꍇ
	if (enemy->nowAttackAttate() == AttackState::None_Attack) {
		const bool WithinShootingDistance = ENParams.ALWAYS_KEEP_DISTANCE_OPEN < distance&& distance < ENParams.RANGE_OF_SHOOTING;
		if (WithinShootingDistance) {
			// �˒��������Ȃ�ASideStep�Ŗ|�M������
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
				// �������Ȃ�m����SideStep�Ŗ|�M������
				return nd_sideStep_;
			}
		}
		//else if (DistanceThatCantBeAnyCloser && DistanceToInitiateMeleeAttack) {
		//	// �ߐڍU���͈͓��Ȃ牽�����Ȃ�
		//	return nullptr;
		//}
		else {
			return nullptr;
		}
	}
}

Node* BhMoveThink::NewActToBeTaken(Node* node) {
	// �s���̍X�V
	if (node != nullptr) {
		lastNode_ = node;
	}
	return lastNode_;
}