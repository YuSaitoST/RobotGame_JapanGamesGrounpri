#include "DeltaTime.h"

float DeltaTime::dt_ = 0.0f;

void DeltaTime::Update(const float deltaTime) {
	dt_ = deltaTime;
}