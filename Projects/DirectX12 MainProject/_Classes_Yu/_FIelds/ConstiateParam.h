#pragma once

#include "_FieldParamsLoad/FieldParamsLoad.h"

#define FLParams ConstiateParam::GetInstance()

class ConstiateParam {
public:
	const float LENGHT_OF_A_SIDE = 800.0f;

public:
	static ConstiateParam& GetInstance() {
		if (instance_ == 0)
			instance_ = new ConstiateParam();
		return *instance_;
	}

	Number GetNumber() const { return param_->GetNumber(); }
	inline float GetFieldFalfScale() const { return field_halfDistance_; }

private:
	ConstiateParam();
	virtual ~ConstiateParam();

	static ConstiateParam* instance_;
	FieldParamsLoad* param_;
	float field_halfDistance_;
};