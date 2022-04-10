#include "BhRandSelector.h"

BhRandSelector::BhRandSelector(Node* node1, Node* node2) {
	std::random_device seed;
	randomEngine_	= std::mt19937(seed());
	randomDist_		= std::uniform_int_distribution<>(0, 1);

	node1_ = node1;
	node2_ = node2;
}

BhRandSelector::~BhRandSelector() {

}

Action BhRandSelector::Behavior(const int myID) {
	if (randomDist_(randomEngine_))
		return node1_->Behavior(myID);
	else
		return node2_->Behavior(myID);
}
