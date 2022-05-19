#include "UIParamsLoad.h"

UIParamsLoad* UIParamsLoad::instance_ = 0;

void UIParamsLoad::LoadParams() {
	FILE* _file;

	auto a = _wfopen_s(&_file, L"_Parameters\\GameUIsPosition.csv", L"r");
	if (a != 0)
		std::abort();

	char _dummyLine[512];
	fgets(_dummyLine, 500, _file);

	fscanf_s(_file, "%f,%f,%f,%f,%f,%f",
		&number_.HP_POS_X,
		&number_.HP_POS_Y,
		&number_.BO_POS_X,
		&number_.BO_POS_Y,
		&number_.MM_POS_X,
		&number_.MM_POS_Y
	);

	fclose(_file);
}