#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes_Yu/_Enemys/_Enemy/_EneState/_ESFighting/_Behavior/_Nodes/Node.h"

class BhShooting : public Node {
public:
	BhShooting() {}
	virtual ~BhShooting() {}

	virtual Action Behavior(const int myID) override;

private:
	float AngleOf2Vector(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b);  // ‚È‚·Šp
};