#pragma once

#include "_FieldParamsLoad/FieldParamsLoad.h"

#define FLParams ConstiateParam::GetInstance()

class ConstiateParam {
public:
	static ConstiateParam& GetInstance() {
		static ConstiateParam instance_;
		return instance_;
	}

	Number GetNumber() const { return param_.GetNumber(); }
	float GetFieldFalfScale() const { return field_halfDistance_ * 0.5f; }

private:
	ConstiateParam() : field_halfDistance_(0.0f) {
		LoadCSV();
		field_halfDistance_ = GetNumber().SCALE * FIELD_SCALE;
	}
	virtual ~ConstiateParam() {}

	void LoadCSV() { param_.LoadParams(); }

	FieldParamsLoad param_;
	float field_halfDistance_;

	const float FIELD_SCALE = 200.0f;
};