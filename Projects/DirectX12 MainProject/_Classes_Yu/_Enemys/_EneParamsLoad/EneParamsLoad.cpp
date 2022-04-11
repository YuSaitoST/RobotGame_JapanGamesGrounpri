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

	fscanf_s(_file, "%f,%f,%f", 
		&number_.DISTANCE_APPROACHING_PLAYER, 
		&number_.SHORTEST_DISTANCE, 
		&number_.SPEED
	);

	number_.SPEED = 0.01f;

	fclose(_file);
}