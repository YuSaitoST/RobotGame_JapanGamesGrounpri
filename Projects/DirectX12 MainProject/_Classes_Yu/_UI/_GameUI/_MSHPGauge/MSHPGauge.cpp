#include "MSHPGauge.h"
#include "_Classes_Yu/_UI/_GameUI/_UIParamsLoad/UIParamsLoad.h"

void MSHPGauge::Initialize() {
	pos_x_ = UIParams.HP_POS_X;
	pos_y_ = UIParams.HP_POS_Y;
}

void MSHPGauge::LoadAssets(DX12::SPRITE bar, DX12::SPRITE frame) {
	sp_bar_ = bar;
	sp_frame_ = frame;
}

void MSHPGauge::Render(DX12::SPRITEBATCH& spriteBatch) {
	//spriteBatch->Draw(
	//	sp_bar_.handle, 
	//	sp_bar_.size, 
	//	RECT(pos_x_, pos_y_, 0, 0), 
	//	nullptr,
	//	DirectX::Colors::White,
	//	0.0f,
	//	DirectX::XMFLOAT2(0.0f, 0.0f),
	//	DirectX::SpriteEffects_None,
	//	0.0f
	//	);
	//spriteBatch->Draw();
}