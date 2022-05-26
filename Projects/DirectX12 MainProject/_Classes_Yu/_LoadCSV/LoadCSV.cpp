#include "LoadCSV.h"
#include <stdio.h>
#include <cstdlib>
#include <cstdarg>

void CSV::Schan(std::wstring fileName, const char* format, ...) {
	FILE* file;

	errno_t nonerror = _wfopen_s(&file, fileName.c_str(), L"r");
	if (nonerror != 0)
		std::abort();

	char _dummyLine[512];
	fgets(_dummyLine, 500, file);

	va_list args;
	va_start(args, format);

	vfscanf_s(file, format, args);

	va_end(args);

	fclose(file);
}

void CSV::Schan(std::wstring fileName, int& numberOfData, std::vector<DirectX::XMFLOAT3>& positionList) {
	FILE* file;

	errno_t nonerror = _wfopen_s(&file, fileName.c_str(), L"r");
	if (nonerror != 0)
		std::abort();

	char _dummyLine[512];
	fgets(_dummyLine, 500, file);

	char _paramLine[512];
	fgets(_paramLine, 500, file);

	std::string _str = std::string(_paramLine);

	Split(_str, numberOfData);
	_str.erase(0, 1);
	for (int i = 0; i < numberOfData; ++i)
		positionList.push_back(Split(_str));

	fclose(file);
}

void CSV::Split(std::string& param, int& numberOfData) {
	const int _cpos = param.find_first_of(',');
	numberOfData = std::stoi(param.substr(0, _cpos));
	param.erase(0, _cpos);
}

DirectX::XMFLOAT3 CSV::Split(std::string& param) {
	DirectX::XMFLOAT3 _pos;

	const int _i = param.find_first_of(':');
	const int _cpos = param.find_first_of(',');
	_pos.x = std::stof(param.substr(0, _i));
	_pos.y = 0.0f;
	_pos.z = std::stof(param.substr(_i + 1, _cpos));
	param.erase(0, _cpos + 1);

	return _pos;
}