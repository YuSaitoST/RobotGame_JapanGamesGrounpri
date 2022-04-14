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

	state_->Update(id_my_);
}

void Enemy::Render(DX9::SKINNEDMODEL& model) {
	model->SetPosition(pos_);
	model->SetRotation(rotate_);
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

void Enemy::Rotate(const float radian) {
	//const SimpleMath::Vector2 _pad = Press.MoveDirection(index);

	//direction_.x = _pad.x * std::sqrtf(1.0f - 0.5f * _pad.x * _pad.y);
	//direction_.y = _pad.y * std::sqrtf(1.0f - 0.5f * _pad.x * _pad.y);
	//direction_.z = 0;

	//prevForward_ = Vector3::Lerp(prevForward_, direction_, deltaTime * 1.0f);
	//rotate_x_ = atan2f(prevForward_.y, prevForward_.x);

	//forward_ = 
	//	(prevForward_ != SimpleMath::Vector3::Zero) ? 
	//	SimpleMath::Vector2(prevForward_.x, prevForward_.y) : 
	//	forward_;
}

Action Enemy::Move(Vector3 forward) {
	forward_ = forward;
	pos_ += forward_ * ENParams.MOVE_SPEED;
	Rotate(0.0f);
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
	pos_.y = ENParams.BACKSTEP_INITIALVELOCITY * jumpTime_ - 0.5f * GRAVITY * jumpTime_ * jumpTime_;

	// ˆÚ“®—ÊŒvŽZ
	const Vector2 nowPosXZ(pos_.x, pos_.z);
	pos_.y = std::min(std::max(0.0f, pos_.y), 5.0f);

	const bool isFine = (pos_.y == 0.0f);

	if (isFine)
		jumpTime_ = 0.0f;

	return isFine ? SUCSESS : REPEAT;
}

Action Enemy::Adjacent() {
	return SUCSESS;
}

Action Enemy::Shooting() {
	return SUCSESS;
}