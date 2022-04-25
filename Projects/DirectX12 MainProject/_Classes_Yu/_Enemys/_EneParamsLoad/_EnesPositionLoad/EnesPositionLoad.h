#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#define ENPos EnesPositionLoad::GetInstance()

using namespace DirectX;

class EnesPositionLoad {
public:
	static EnesPositionLoad& GetInstance() {
		if (instance_ == 0)
			instance_ = new EnesPositionLoad();

		return *instance_;
	}

	void LoadParams();
	XMFLOAT3 GetPosition(const int id) const { return pos_[id]; }

private:
	EnesPositionLoad() : pos_{} {}
	virtual ~EnesPositionLoad() {}

	XMFLOAT3 Split(std::string& param);

	static EnesPositionLoad* instance_;
	XMFLOAT3 pos_[15];
};