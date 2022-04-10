#include "Enemy.h"

Enemy::Enemy() {
	cp_ = nullptr;
	SetMember(OBJ_TYPE::NONE_OBJ_ID, Vector3::Zero, 1.0f);

	state_ = nullptr;
}

Enemy::Enemy(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(OBJ_TYPE::ENEMY, pos, r);

	SwitchState(SPONE);
}

Enemy::~Enemy() {

}

void Enemy::Initialize(const int id) {
	id_my_ = id;
}

void Enemy::Update(const float deltaTime) {
	state_->Update(id_my_);
}

void Enemy::Render(DX9::SKINNEDMODEL& model) {
	model->SetPosition(pos_);
	model->Draw();
}

void Enemy::SwitchState(ENE_STATE state) {
	switch (state) {
		case SPONE		: state_ = &st_spone_;		break;
		case STANDBY	: state_ = &st_standby_;	break;
		case FIGHTING	: state_ = &st_fighting_;	break;
		case STAN:break;
		case DOWN:break;
	}
}

void Enemy::Move(Vector3 forward) {
	pos_ += forward * ENParams.SPEED;
}

void Enemy::Adjacent() {

}