#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/EneState.h"

class ESSpone : public EneState {
public:
	ESSpone() {}
	virtual ~ESSpone() {}

	virtual void Update(const int myID) override;
};