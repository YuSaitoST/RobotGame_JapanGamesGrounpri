#pragma once

#include "Base/pch.h"

namespace Field {
	void ClampPosition(DirectX::SimpleMath::Vector3& position);
	bool IsOut(DirectX::SimpleMath::Vector3 position);
}