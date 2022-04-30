#include "Bullet.h"
#include "_Classes_Yu/_FieldOutCheck/FieldOutCheck.h"

Bullet::Bullet() {
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::WEAPON, Vector3::Zero, 1.0f);
}

void Bullet::Update(const float deltaTime) {
	pos_ += forward_  * 90.0f * deltaTime;

	if (Field::IsOut(pos_)) {
		pos_ = Vector3::Zero;
		isAttack_ = false;
	}

	UpdateToMorton();
}

void Bullet::Render(DX9::MODEL& model) {
	model->Draw();
	model->SetPosition(pos_);
}

void Bullet::Shoot(int ownerID, int damage, Vector3 pos, Vector3 forward, float rotY) {
	isAttack_	= true;
	id_my_		= ownerID;
	damage_		= damage;
	pos_		= Vector3(pos.x, 2.0f, pos.z);
	rotateY_	= rotY;
	forward_	= forward;
}