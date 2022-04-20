#include "ConstiateParam.h"

ConstiateParam* ConstiateParam::instance_;

ConstiateParam::ConstiateParam() {
	param_ = new FieldParamsLoad();
	param_->LoadParams();
	field_halfDistance_ = GetNumber().SCALE * LENGHT_OF_A_SIDE * 0.5f;
}

ConstiateParam::~ConstiateParam() {
	delete param_;
}