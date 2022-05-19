#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class MiniMap {
public:
	MiniMap() : pos_x_(0.0f), pos_y_(0.0f) {}
	virtual ~MiniMap() {}

	void Initialize();
	void LoadAssets();
	void Render() const;

private:
	DX9::SPRITE sprite_;
	float pos_x_;
	float pos_y_;
};