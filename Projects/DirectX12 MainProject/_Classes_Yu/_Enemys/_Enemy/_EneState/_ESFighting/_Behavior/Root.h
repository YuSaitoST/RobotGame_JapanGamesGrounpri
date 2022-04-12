#pragma once

#include <vector>
#include "_Nodes/Node.h"

class Root {
public:
	Root();
	virtual ~Root();

	void Update(const int myID);

private:
	std::vector<Node*> nodeList_;
};