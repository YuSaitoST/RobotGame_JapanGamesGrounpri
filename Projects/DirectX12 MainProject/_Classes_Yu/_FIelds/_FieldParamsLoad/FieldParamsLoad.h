#pragma once

struct Number {
	float HP;
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