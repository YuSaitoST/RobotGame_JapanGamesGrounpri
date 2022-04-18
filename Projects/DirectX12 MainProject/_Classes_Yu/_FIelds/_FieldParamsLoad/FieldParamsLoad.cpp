#include "FieldParamsLoad.h"
#include <stdio.h>
#include <cstdlib>

FieldParamsLoad* FieldParamsLoad::instance_ = 0;

void FieldParamsLoad::LoadParams() {
	FILE* _file;

	auto a = _wfopen_s(&_file, L"_Parameters\\FieldParams.csv", L"r");
	if (a != 0)
		std::abort();

	char _dummyLine[256];
	fgets(_dummyLine, 255, _file);

	fscanf_s(_file, "%f",
		&number_.SCALE
	);

	// �\���̂�z��ň����A���[�v�Ń`�F�b�N����
	float* ptr = (float*)&number_;
	for (int i = 0; i < 1; ++i) {
		if (*ptr <= 0.0)
			std::abort();
		ptr++;
	}

	fclose(_file);
}