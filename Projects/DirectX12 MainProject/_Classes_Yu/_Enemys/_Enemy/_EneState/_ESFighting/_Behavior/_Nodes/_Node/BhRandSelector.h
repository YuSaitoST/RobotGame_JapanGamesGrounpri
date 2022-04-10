#pragma once

#include <random>
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"

class BhRandSelector : public Node {
public:
	BhRandSelector(Node* node1, Node* node2);
	virtual ~BhRandSelector();

	virtual Action Behavior(const int myID) override;

private:
	std::mt19937 randomEngine_;
	std::uniform_int_distribution<> randomDist_;

	Node* node1_;
	Node* node2_;
};