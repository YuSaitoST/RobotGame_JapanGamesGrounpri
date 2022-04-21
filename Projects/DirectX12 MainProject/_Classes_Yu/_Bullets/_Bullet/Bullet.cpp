#include "Bullet.h"
#include "_Classes_Yu/_FieldOutCheck/FieldOutCheck.h"

Bullet::Bullet() : isShot_(false) {
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::WEAPON, Vector3::Zero, 1.0f);
}

void Bullet::Update(const float deltaTime) {
	pos_ += forward_  * 70.0f * deltaTime;

	if (Field::IsOut(pos_)) {
		pos_ = Vector3::Zero;
		isShot_ = false;
	}

	UpdateToMorton();
}

void Bullet::Render(DX9::MODEL& model) {
	model->Draw();
	model->SetPosition(pos_);
}

void Bullet::Shoot(int ownerID, Vector3 pos, Vector3 forward, float rotY) {
	isShot_		= true;
	id_my_		= ownerID;
	pos_		= Vector3(pos.x, 1.5f, pos.z);
	rotateY_	= rotY;
	forward_	= forward;
}