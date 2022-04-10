#include "BhWarSelector.h"
#include "_Nd_Attack/BhShooting.h"
#include "_Nd_Attack/BhAdjacent.h"

BhWarSelector::BhWarSelector() {
	nd_escape_ = new BhEscapeThink();
	nd_random_ = new BhRandSelector(new BhShooting(), new BhAdjacent());
}

BhWarSelector::~BhWarSelector() {

}

Action BhWarSelector::Behavior(const int myID) {
	return (nd_escape_->Behavior(myID) != FAILIRE) ? SUCSESS : nd_random_->Behavior(myID);
}