#include "FieldOutCheck.h"
#include "_Classes_Yu/_FIelds/_Parameter/ConstiateParam.h"

void Field::ClampPosition(DirectX::SimpleMath::Vector3& position) {
	position.x = std::min(std::max(0.0f, position.x), FLParams.LENGHT_OF_A_SIDE);
	position.z = std::min(std::max(0.0f, position.z), FLParams.LENGHT_OF_A_SIDE);
}

bool Field::IsOut(DirectX::SimpleMath::Vector3 position) {
	const bool isOutX = (position.x < 0.0f) || (FLParams.LENGHT_OF_A_SIDE < position.x);
	const bool isOutZ = (position.z < 0.0f) || (FLParams.LENGHT_OF_A_SIDE < position.z);

	return isOutX || isOutZ;
}