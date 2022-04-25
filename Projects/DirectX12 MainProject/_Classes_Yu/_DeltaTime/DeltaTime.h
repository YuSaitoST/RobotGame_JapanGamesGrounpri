#pragma once

class DeltaTime {
public:
	static void Update(const float deltaTime);
	static float dt() { return dt_; }

private:
	DeltaTime() {}
	static float dt_;
};