#pragma once

#include "_Classes_Yu/_Enemys/_Enemy/_EneState/EneState.h"
#include "_Classes_Yu/_UI/_OriTimer/OriTimer.h"

class ESStan final : public EneState {
public:
	ESStan();
	virtual ~ESStan();

	virtual void Update(const int myID) override;

private:
	OriTimer* timer_;
};