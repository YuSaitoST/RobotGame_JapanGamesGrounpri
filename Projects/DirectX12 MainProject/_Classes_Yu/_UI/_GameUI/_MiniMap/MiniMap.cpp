#include "MiniMap.h"
#include "_Classes_Yu/_UI/_GameUI/_UIParamsLoad/UIParamsLoad.h"

void MiniMap::Initialize() {
	pos_x_ = UIParams.MM_POS_X;
	pos_y_ = UIParams.MM_POS_Y;
}

void MiniMap::LoadAssets() {
	sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Main\\sp_miniMapBG.png");
}

void MiniMap::Render() const {
	DX9::SpriteBatch->DrawSimple(sprite_.Get(), DirectX::SimpleMath::Vector3(pos_x_, pos_y_, 0.0f));
}