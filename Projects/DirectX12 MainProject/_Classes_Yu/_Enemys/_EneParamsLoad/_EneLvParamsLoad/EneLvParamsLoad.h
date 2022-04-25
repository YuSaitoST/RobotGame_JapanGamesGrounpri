#pragma once

#include <string>

#define ENLParams EneLvParamsLoad::GetInstance().GetNumber()

enum LEVELS { ONE = 0, TWO = 1, THREE = 2 };

class EneLvParamsLoad {
public:
	struct Number {
		int HP[3];
		float SPEED_OF_ACTION[3];
		float SPEED_OF_BULLET[3];
		float DAMAGE_ADJ[3];
		float DAMAGE_SHO[3];
	};

	static EneLvParamsLoad& GetInstance() {
		if (instance_ == 0)
			instance_ = new EneLvParamsLoad();

		return *instance_;
	}

	void LoadParams();
	Number GetNumber() const { return number_; }

private:
	EneLvParamsLoad() : number_{} {}
	virtual ~EneLvParamsLoad() {}

	void Split(std::string& str, int(&list)[]);
	void Split(std::string& str, float(&list)[]);

	static EneLvParamsLoad* instance_;
	Number number_;
};