#pragma once

#include <algorithm>

class OriTimer {
public:
	OriTimer(float countTime);
	OriTimer(float countTime, float startTime);
	virtual ~OriTimer() = default;

	void Update(const float deltaTime);
	void ResetCountTime() { time_ = max_; };

	inline float NowTime() const { return time_; };
	inline bool TimeOut() const { return (time_ <= 0.0f); };

private:
	float				max_;
	float				time_;
};