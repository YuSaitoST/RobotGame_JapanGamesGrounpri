#include "Enemy.h"

Enemy::Enemy() {
	cp_ = nullptr;
	SetMember(OBJ_TYPE::NONE_OBJ_ID, Vector3::Zero, 1.0f);

	state_ = nullptr;
	isHitPlayer_ = false;
}

Enemy::Enemy(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(OBJ_TYPE::ENEMY, pos, r);

	SwitchState(SPONE);

	forward_ = Vector3(0.0f, 0.0f, -1.0f);
	isHitPlayer_ = false;

	amountOfBackStep_ = 0.0f;

	timeDelta_ = 0.0f;
	jumpTime_ = 0.0f;
}

Enemy::~Enemy() {

}

void Enemy::Initialize(const int id) {
	id_my_ = id;
}

void Enemy::Update(const float deltaTime) {
	timeDelta_ = deltaTime;

	ObjectBase* hitObj = IsHitObject();
	isHitPlayer_ = (hitObj != nullptr) ? (hitObj->myObjectType() == OBJ_TYPE::PLAYER) : false;

	//state_->Update(id_my_);
	BackStep();
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

Action Enemy::Move(Vector3 forward) {
	pos_ += forward * ENParams.MOVE_SPEED;
	return SUCSESS;
}

Action Enemy::Thruster() {
	return SUCSESS;
}

Action Enemy::BackStep() {
	const Vector2 oldPosXZ(pos_.x, pos_.z);
	jumpTime_ += timeDelta_;

	// ˆÚ“®ŒvŽZ
	pos_ += -forward_ * ENParams.BACKSTEP_SPEED;
	pos_.y += 3.0f * jumpTime_ - 0.5f * GRAVITY * jumpTime_ * jumpTime_;

	// ˆÚ“®—ÊŒvŽZ(x-z‚Í‚¢‚ç‚È‚¢‚ÆŽv‚¤)
	const Vector2 nowPosXZ(pos_.x, pos_.z);
	amountOfBackStep_ += std::fabsf((nowPosXZ - oldPosXZ).Length());
	pos_.y = std::min(std::max(0.0f, pos_.y), 5.0f);

	const bool isFine = (pos_.y == 0.0f);

	if (isFine)
		amountOfBackStep_ = 0.0f;

	return isFine ? SUCSESS : REPEAT;
}

Action Enemy::Adjacent() {
	return SUCSESS;
}

Action Enemy::Shooting() {
	return SUCSESS;
}