#pragma once

#include "Base/pch.h"

using namespace DirectX;

class bsCollBox {
public:
	bsCollBox() { colli = BoundingBox{}; };
	virtual ~bsCollBox() = default;

	void SetPosition(SimpleMath::Vector3 pos) { colli.Center = pos; };

	void SetColli(BoundingBox bound) { colli = bound; };

	BoundingBox GetBounding() const { return colli; };

private:
	BoundingBox colli;
};