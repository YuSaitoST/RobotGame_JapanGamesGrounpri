#include "EnesPositionLoad.h"
#include <stdio.h>
#include <cstdlib>

EnesPositionLoad* EnesPositionLoad::instance_ = 0;

void EnesPositionLoad::LoadParams() {
	FILE* _file;

	auto _a = _wfopen_s(&_file, L"_Parameters\\EnemysPosition.csv", L"r");
	if (_a != 0)
		std::abort();

	char _dummyLine[512];
	fgets(_dummyLine, 500, _file);

	char _posList[256];
	fscanf(_file, "%s", &_posList);
	std::string _str = std::string(_posList);
	pos_[0] = Split(_str);
	pos_[1] = Split(_str);
	pos_[2] = Split(_str);
	pos_[3] = Split(_str);
	pos_[4] = Split(_str);
	pos_[5] = Split(_str);
	pos_[6] = Split(_str);
	pos_[7] = Split(_str);
	pos_[8] = Split(_str);
	pos_[9] = Split(_str);
	pos_[10] = Split(_str);
	pos_[11] = Split(_str);
	pos_[12] = Split(_str);
	pos_[13] = Split(_str);
	pos_[14] = Split(_str);

	fclose(_file);
}

XMFLOAT3 EnesPositionLoad::Split(std::string& param) {
	XMFLOAT3 _pos;

	const int _i = param.find_first_of(':');
	const int _cpos = param.find_first_of(',');
	_pos.x = std::stof(param.substr(0, _i));
	_pos.y = 0.0f;
	_pos.z = std::stof(param.substr(_i + 1, _cpos));
	param.erase(0, _cpos + 1);
	
	return _pos;
}