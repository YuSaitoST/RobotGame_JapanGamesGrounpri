#pragma once

#define FLParams FieldParamsLoad::GetInstance().GetNumber()

class FieldParamsLoad {
public:
	struct Number {
		float SCALE;
	};

	static FieldParamsLoad& GetInstance() {
		if (instance_ == 0)
			instance_ = new FieldParamsLoad();

		return *instance_;
	}

	void LoadParams();
	Number GetNumber() const { return number_; }

private:
	FieldParamsLoad() : number_{} {}
	virtual ~FieldParamsLoad() {}

	static FieldParamsLoad* instance_;
	Number number_;
};