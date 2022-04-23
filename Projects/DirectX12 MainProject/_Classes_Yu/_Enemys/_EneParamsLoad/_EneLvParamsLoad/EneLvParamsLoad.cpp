#include "EneLvParamsLoad.h"
#include <stdio.h>
#include <cstdlib>

EneLvParamsLoad* EneLvParamsLoad::instance_ = 0;

void EneLvParamsLoad::LoadParams() {
	FILE* _file;

	auto a = _wfopen_s(&_file, L"_Parameters\\EnemyLevelsParams.csv", L"r");
	if (a != 0)
		std::abort();

	char _dummyLine[256];
	fgets(_dummyLine, 255, _file);

	char _hp, _soa, _sob, _oaa, _oas;

	fscanf_s(_file, "%s", _hp);

	//fscanf_s(_file, "%s,%s,%s,%s,%s",
	//	_hp, _countof(20),
	//	_soa,
	//	_sob,
	//	_oaa,
	//	_oas
	//);

	Split(&_hp, number_.HP);
	//Split(&_soa, number_.SPEED_OF_ACTION);
	//Split(&_sob, number_.SPEED_OF_BULLET);
	//Split(&_oaa, number_.OFFENSIVE_ABILITY_ADJ);
	//Split(&_oas, number_.OFFENSIVE_ABILITY_SHO);

	fclose(_file);
}

void EneLvParamsLoad::Split(std::string str, int* list) {
	int first = 0;
	int last = str.find_first_of(':');

	for (int _i = 0; _i < 3; ++_i) {
		const std::string s = str.substr(first, last - first);
		list[_i] = std::stoi(s.c_str());
		first = last + 1;
		last = str.find_first_of(s.size() + 2, first);
	}
}

void EneLvParamsLoad::Split(std::string str, float* list) {
	int first = 0;
	int last = str.find_first_of(':');

	for (int _i = 0; _i < 3; ++_i) {
		const std::string s = str.substr(first, last - first);
		list[_i] = std::stof(s.c_str());
		first = last + 1;
		last = str.find_first_of(s.size() + 2, first);
	}
}