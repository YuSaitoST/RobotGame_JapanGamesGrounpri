#include "EneLvParamsLoad.h"
#include <stdio.h>
#include <cstdlib>

EneLvParamsLoad* EneLvParamsLoad::instance_ = 0;

void EneLvParamsLoad::LoadParams() {
	FILE* _file;

	auto _a = _wfopen_s(&_file, L"_Parameters\\EnemyLevelsParams.csv", L"r");
	if (_a != 0)
		std::abort();

	char _dummyLine[256];
	fgets(_dummyLine, 255, _file);

	char _paramList[256];
	fscanf(_file, "%s", &_paramList);

	if (_paramList == "")
		std::abort();

	std::string _str = std::string(_paramList);

	Split(_str, number_.HP);
	Split(_str, number_.SPEED_OF_ACTION);
	Split(_str, number_.SPEED_OF_STEP);
	Split(_str, number_.SPEED_OF_BULLET);
	Split(_str, number_.DAMAGE_ADJ);
	Split(_str, number_.DAMAGE_SHO);

	fclose(_file);
}

void EneLvParamsLoad::Split(std::string& str, int(&list)[]) {
	int _clpos = str.find_first_of(':');
	list[LEVELS::ONE] = std::stoi(str.substr(0, _clpos));
	str.erase(0, _clpos + 1);
	_clpos = str.find_first_of(':');
	list[LEVELS::TWO] = std::stoi(str.substr(0, _clpos));
	const int _cnpos = str.find_first_of(',');
	str.erase(0, _cnpos + 1);
}

void EneLvParamsLoad::Split(std::string& str, float(&list)[]) {
	int _clpos = str.find_first_of(':');
	list[LEVELS::ONE] = std::stof(str.substr(0, _clpos));
	str.erase(0, _clpos + 1);
	_clpos = str.find_first_of(':');
	list[LEVELS::TWO] = std::stof(str.substr(0, _clpos));
	const int _cnpos = str.find_first_of(',');
	str.erase(0, _cnpos + 1);
}