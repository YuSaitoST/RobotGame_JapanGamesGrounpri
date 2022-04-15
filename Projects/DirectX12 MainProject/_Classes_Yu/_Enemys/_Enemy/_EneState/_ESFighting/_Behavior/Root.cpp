#include "Root.h"
#include "_Nodes/_Node/_Nd_Move/BhMoveThink.h"
#include "_Nodes/_Node/_Nd_War/BhWarSelector.h"

Root::Root() {
	nodeList_.reserve(2);
	nodeList_.push_back(new BhMoveThink());
	nodeList_.push_back(new BhWarSelector());
}

Root::~Root() {

}

void Root::Update(const int myID) {
	for (Node* node : nodeList_)
		node->Behavior(myID);
		//if (node->Behavior(myID) == Action::FAILIRE)
		//	break;
}