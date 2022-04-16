#pragma once

#define ENParams EneParamsLoad::GetInstance().GetNumber()

enum ENE_STATE { SPONE, STANDBY, FIGHTING, STAN, DOWN };

class EneParamsLoad {
public:
	struct Number {
		float DISTANCE_APPROACHING_PLAYER;
		float SHORTEST_DISTANCE;
		float MOVE_SPEED;
		float STEP_SPEED;
		float STEP_INITIALVELOCITY;
		float STEP_DISTANCE;
		float RANGE_OF_SHOT;
		float FREQUENCY_OF_SHOOTING;
		float SWITCH_TO_MELEEATTACK;
		float MELEEATTACK_TO_DISTANCE;
	};

	static EneParamsLoad& GetInstance() {
		if (instance_ == 0)
			instance_ = new EneParamsLoad();

		return *instance_;
	}

	void LoadParams();
	Number GetNumber() const { return number_; }

private:
	EneParamsLoad() : number_{} {}
	virtual ~EneParamsLoad() {}

	static EneParamsLoad* instance_;
	Number number_;
};