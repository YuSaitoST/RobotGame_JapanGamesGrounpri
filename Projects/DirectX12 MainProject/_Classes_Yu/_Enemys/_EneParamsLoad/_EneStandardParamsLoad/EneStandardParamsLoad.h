#pragma once

#define ENParams EneStandardParamsLoad::GetInstance().GetNumber()

enum ENE_STATE { STANDBY, FIGHTING, STAN, DOWN };

class EneStandardParamsLoad {
public:
	struct Number {
		float MOB_RIGHT_END[2];
		float MOB_LEFT_END[2];
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

	static EneStandardParamsLoad& GetInstance() {
		if (instance_ == 0)
			instance_ = new EneStandardParamsLoad();

		return *instance_;
	}

	void LoadParams();
	Number GetNumber() const { return number_; }

private:
	EneStandardParamsLoad() : number_{} {}
	virtual ~EneStandardParamsLoad() {}

	static EneStandardParamsLoad* instance_;
	Number number_;
};