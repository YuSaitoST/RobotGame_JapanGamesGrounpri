#pragma once

enum Action { SUCSESS, FAILIRE, ROOPING };

class Node {
public:
	Node() : next_(nullptr) {}
	virtual ~Node() {}
	virtual Action Behavior(const int myID) = 0;

protected:
	Node* next_;
};