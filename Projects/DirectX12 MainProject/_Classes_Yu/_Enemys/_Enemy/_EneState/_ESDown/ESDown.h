#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/EneState.h"

class ESDown final : public EneState {
public:
	ESDown() {}
	virtual ~ESDown() {}

	virtual void Update(const int myID) override;
};