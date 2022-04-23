#include "EnesPositionLoad.h"
#include <stdio.h>
#include <cstdlib>

EnesPositionLoad* EnesPositionLoad::instance_ = 0;

void EnesPositionLoad::LoadParams() {
	FILE* _file;

	auto a = _wfopen_s(&_file, L"_Parameters\\EnemysPosition.csv", L"r");
	if (a != 0)
		std::abort();

	char _dummyLine[512];
	fgets(_dummyLine, 500, _file);

	char posList[256];
	fscanf(_file, "%s", &posList);
	std::string str = std::string(posList);
	pos_[0] = Split(str);
	pos_[1] = Split(str);
	pos_[2] = Split(str);
	pos_[3] = Split(str);
	pos_[4] = Split(str);
	pos_[5] = Split(str);
	pos_[6] = Split(str);
	pos_[7] = Split(str);
	pos_[8] = Split(str);
	pos_[9] = Split(str);
	pos_[10] = Split(str);
	pos_[11] = Split(str);
	pos_[12] = Split(str);
	pos_[13] = Split(str);

	fclose(_file);
}

XMFLOAT3 EnesPositionLoad::Split(std::string& param) {
	XMFLOAT3 pos;

	const int _i = param.find_first_of(':');
	const int cpos = param.find_first_of(',');
	pos.x = std::stof(param.substr(0, _i));
	pos.y = 0.0f;
	pos.z = std::stof(param.substr(_i + 1, cpos));
	param.erase(0, cpos + 1);
	
	return pos;
}