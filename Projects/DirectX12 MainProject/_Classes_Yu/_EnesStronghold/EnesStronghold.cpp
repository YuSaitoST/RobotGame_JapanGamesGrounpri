#include "EnesStronghold.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EnesPositionLoad/EnesPositionLoad.h"

EnesStronghold::EnesStronghold() {
	cp_ = nullptr;
	pos_ = ENPos.GetPosition(14);
	pos_.y = 15.0f;
	SetBaseMember(BASE, pos_, 1.0f);
}

void EnesStronghold::LoadAssets() {
	mod_base_ = DX9::Model::CreateBox(DXTK->Device9, 30.0f, 30.0f, 30.0f);
	mod_base_->SetPosition(pos_);

	UpdateToMorton();
}

void EnesStronghold::Update(const float deltaTime) {
	// ƒqƒbƒg”»’è‚ðs‚¤
}

void EnesStronghold::Render() {
	mod_base_->Draw();
}