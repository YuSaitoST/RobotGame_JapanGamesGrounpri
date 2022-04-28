#pragma once

enum SCORE {
	BREAK_ENEMY = 100,
	BREAK_BASE = 1000
};

class TotalScore {
public:
	TotalScore() : score_(0) {};
	virtual ~TotalScore() {}

	void Addition(SCORE score) { score_ += (int)score; }
	inline int GetScore() const { return score_; }

private:
	int score_;
};