#pragma once

enum Action { SUCSESS, FAILIRE, REPEAT };

class Node {
public:
	Node() {}
	virtual ~Node() {}
	virtual Action Behavior(const int myID) = 0;
};