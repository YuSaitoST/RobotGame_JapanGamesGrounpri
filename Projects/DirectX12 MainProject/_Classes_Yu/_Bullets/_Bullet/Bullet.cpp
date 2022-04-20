#include "Bullet.h"

Bullet::Bullet() : isShot_(false) {
	SetBaseMember(OBJ_TYPE::WEAPON, Vector3::Zero, 1.0f);
}

void Bullet::Update(const float deltaTime) {
	pos_ += forward_ * deltaTime;
	UpdateToMorton();
}

void Bullet::Render(DX9::MODEL& model) {
	model->Draw();
}

void Bullet::Shoot(int ownerID, Vector3 pos, float rotY) {
	isShot_		= true;
	id_my_		= ownerID;
	pos_		= pos;
	rotateY_	= rotY;
	SetFlyForward();
}

void Bullet::SetFlyForward() {
	D3DXVECTOR3 vout(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vbase(1.0f, 0.0f, 0.0f);
	D3DXMATRIX	mat{};
	D3DXMatrixRotationY(&mat, rotateY_);
	D3DXVec3TransformCoord(&vout, &vbase, &mat);
	forward_ = Vector3(vout.x, vout.y, vout.z);
}