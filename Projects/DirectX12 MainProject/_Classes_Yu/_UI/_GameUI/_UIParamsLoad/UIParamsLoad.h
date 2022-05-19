#pragma once

#include <string>

#define UIParams UIParamsLoad::GetInstance().GetNumber()

class UIParamsLoad {
public:
	struct Number {
		float HP_POS_X;
		float HP_POS_Y;
		float BO_POS_X;
		float BO_POS_Y;
		float MM_POS_X;
		float MM_POS_Y;
	};

	static UIParamsLoad& GetInstance() {
		if (instance_ == 0)
			instance_ = new UIParamsLoad();

		return *instance_;
	}

	void LoadParams();
	Number GetNumber() const { return number_; }

private:
	UIParamsLoad() : number_{} {}
	virtual ~UIParamsLoad() {}

	void Split(std::string& str, int(&list)[]);
	void Split(std::string& str, float(&list)[]);

	static UIParamsLoad* instance_;
	Number number_;
};