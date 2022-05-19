#include "EneStandardParamsLoad.h"
#include <stdio.h>
#include <cstdlib>

EneStandardParamsLoad* EneStandardParamsLoad::instance_ = 0;

void EneStandardParamsLoad::LoadParams() {
	FILE* _file;

	auto a = _wfopen_s(&_file, L"_Parameters\\EnemyParams.csv", L"r");
	if (a != 0)
		std::abort();

	char _dummyLine[512];
	fgets(_dummyLine, 500, _file);

	fscanf_s(_file, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		&number_.MOB_RIGHT_END[0],
		&number_.MOB_RIGHT_END[1],
		&number_.MOB_LEFT_END[0],
		&number_.MOB_LEFT_END[1],
		&number_.DISTANCE_TO_NOTICE_PLAYER,
		&number_.RANGE_OF_SHOOTING,
		&number_.ALWAYS_KEEP_DISTANCE_OPEN,
		&number_.RANGE_OF_MELEEATTACK,
		&number_.UNAPPROACHABLE_DISTANCE,
		&number_.STEP_INITIALVELOCITY,
		&number_.STEP_DISTANCE,
		&number_.FREQUENCY_OF_SHOOTING
	);

	// 構造体を配列で扱い、ループでチェックする
	float* ptr = (float*)&number_;
	ptr += 4;
	for (int i = 4; i < 10; ++i) {
		if (*ptr <= 0.0f)
			std::abort();
		ptr++;
	}

	fclose(_file);
}