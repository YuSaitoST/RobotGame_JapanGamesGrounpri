#pragma once

#define ENParams EneStandardParamsLoad::GetInstance().GetNumber()

enum class ENE_STATE { STANDBY, FIGHTING, STAN, DOWN };

class EneStandardParamsLoad {
public:
	struct Number {
		float MOB_RIGHT_END[2];
		float MOB_LEFT_END[2];
		float DISTANCE_TO_NOTICE_PLAYER;	// [ e ]
		float RANGE_OF_SHOOTING;			// [ d ] 
		float ALWAYS_KEEP_DISTANCE_OPEN;	// [ c ]
		float RANGE_OF_MELEEATTACK;			// [ b ]
		float UNAPPROACHABLE_DISTANCE;		// [ a ]
		float STEP_INITIALVELOCITY;
		float STEP_DISTANCE;
		float FREQUENCY_OF_SHOOTING;
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