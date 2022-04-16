#include "EneParamsLoad.h"
#include <stdio.h>
#include <cstdlib>

EneParamsLoad* EneParamsLoad::instance_ = 0;

void EneParamsLoad::LoadParams() {
	FILE* _file;

	auto a = _wfopen_s(&_file, L"_Parameters\\EnemyParams.csv", L"r");
	if (a != 0)
		std::abort();

	char _dummyLine[256];
	fgets(_dummyLine, 255, _file);

	fscanf_s(_file, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		&number_.DISTANCE_APPROACHING_PLAYER,
		&number_.SHORTEST_DISTANCE,
		&number_.MOVE_SPEED,
		&number_.STEP_SPEED,
		&number_.STEP_INITIALVELOCITY,
		&number_.STEP_DISTANCE,
		&number_.RANGE_OF_SHOT,
		&number_.FREQUENCY_OF_SHOOTING,
		&number_.SWITCH_TO_MELEEATTACK,
		&number_.MELEEATTACK_TO_DISTANCE
	);

	const float FLSIZE = sizeof(float);
	const float* ma = &number_.DISTANCE_APPROACHING_PLAYER;
	const float* mb = &number_.SHORTEST_DISTANCE;
	const float* mc = &number_.MOVE_SPEED;
	const float* md = &number_.STEP_SPEED;
	const float* me = &number_.STEP_INITIALVELOCITY;
	const float* mf = &number_.STEP_DISTANCE;
	const float* mg = &number_.RANGE_OF_SHOT;
	const float* mh = &number_.FREQUENCY_OF_SHOOTING;
	const float* mi = &number_.SWITCH_TO_MELEEATTACK;
	const float* mj = &number_.MELEEATTACK_TO_DISTANCE;

	fclose(_file);
}