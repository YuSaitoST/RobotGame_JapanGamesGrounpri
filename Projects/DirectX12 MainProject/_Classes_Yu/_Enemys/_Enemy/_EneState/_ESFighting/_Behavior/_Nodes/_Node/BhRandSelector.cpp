#include "BhRandSelector.h"

BhRandSelector::BhRandSelector(Node* node1, Node* node2) {
	std::random_device seed;
	randomEngine_	= std::mt19937(seed());
	randomDist_		= std::uniform_int_distribution<>(0, 1);

	node1_ = node1;
	node2_ = node2;

	lastAction_ = FAILIRE;
	lastActionNum_ = -1;
}

BhRandSelector::~BhRandSelector() {
	delete node2_;
	delete node1_;
}

Action BhRandSelector::Behavior(const int myID) {
	if (lastAction_ == REPEAT) {
		if (lastActionNum_)
			lastAction_ = node1_->Behavior(myID);
		else
			lastAction_ = node2_->Behavior(myID);

		return lastAction_;
	}

	const int nowActionNumber = randomDist_(randomEngine_);
	if (nowActionNumber)
		lastAction_ = node1_->Behavior(myID);
	else
		lastAction_ = node2_->Behavior(myID);

	lastActionNum_ = randomDist_(randomEngine_);
	return lastAction_;
}
