#pragma once

struct Number {
	float SCALE;
};

class FieldParamsLoad {
public:
	FieldParamsLoad() : number_{} {}
	virtual ~FieldParamsLoad() {}

	void LoadParams();
	Number GetNumber() const { return number_; }

private:
	Number number_;
};