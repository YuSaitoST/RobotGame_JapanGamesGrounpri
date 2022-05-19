#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class MSHPGauge {
public:
	MSHPGauge() : pos_x_(0.0f), pos_y_(0.0f) {}
	virtual ~MSHPGauge() {}

	void Initialize();
	void LoadAssets(DX12::SPRITE bar, DX12::SPRITE frame);
	void Render(DX12::SPRITEBATCH& spriteBatch);

private:
	DX12::SPRITE sp_bar_;
	DX12::SPRITE sp_frame_;
	float pos_x_;
	float pos_y_;
};