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

	fscanf_s(_file, "%f,%f,%f,%f,%f,%f,%f,%f", 
		&number_.DISTANCE_APPROACHING_PLAYER, 
		&number_.SHORTEST_DISTANCE, 
		&number_.MOVE_SPEED,
		&number_.BACKSTEP_SPEED,
		&number_.BACKSTEP_INITIALVELOCITY,
		&number_.BACKSTEP_DISTANCE,
		&number_.RANGE_OF_SHOT,
		&number_.FREQUENCY_OF_SHOOTING
	);

	const float FLSIZE = sizeof(float);
	const float* ma = &number_.DISTANCE_APPROACHING_PLAYER;
	const float* mb = &number_.SHORTEST_DISTANCE;
	const float* mc = &number_.MOVE_SPEED;
	const float* md = &number_.BACKSTEP_SPEED;
	const float* me = &number_.BACKSTEP_INITIALVELOCITY;
	const float* mf = &number_.BACKSTEP_DISTANCE;
	const float* mg = &number_.RANGE_OF_SHOT;
	const float* mh = &number_.FREQUENCY_OF_SHOOTING;

	fclose(_file);
}