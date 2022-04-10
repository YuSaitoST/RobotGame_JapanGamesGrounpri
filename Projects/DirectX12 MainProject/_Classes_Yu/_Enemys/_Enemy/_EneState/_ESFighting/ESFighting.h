#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/EneState.h"
#include "_Behavior/Root.h"

class ESFighting final : public EneState {
public:
	ESFighting();
	virtual ~ESFighting();

	virtual void Update(const int myID) override;

private:
	Root* root_;
};