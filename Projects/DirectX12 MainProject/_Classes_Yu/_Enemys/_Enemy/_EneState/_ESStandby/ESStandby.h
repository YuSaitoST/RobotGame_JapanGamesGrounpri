#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/EneState.h"

class ESStandby final : public EneState {
public:
	ESStandby() {}
	virtual ~ESStandby() {}

	virtual void Update(const int myID) override;
};