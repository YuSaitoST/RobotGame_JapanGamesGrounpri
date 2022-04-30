#include "MeleeWeapon.h"
#include "_Classes_Yu/_FieldOutCheck/FieldOutCheck.h"

MeleeWeapon::MeleeWeapon() {
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::WEAPON, Vector3::Zero, 1.0f);
}

void MeleeWeapon::Initialize(const int id) {
	id_my_ = id;
}

void MeleeWeapon::LoadAssets() {
	mod_ = DX9::Model::CreateBox(DXTK->Device9, 1.0f, 2.5f, 1.0f);
}

void MeleeWeapon::Render() {
	mod_->Draw();
}

void MeleeWeapon::UpdatePosition(Vector3 position, Vector3 forward) {
	pos_ = position + forward * ADJUSTMENT;
	pos_.y = 2.0f;
	Field::ClampPosition(pos_);
	mod_->SetPosition(pos_);
	UpdateToMorton();
}