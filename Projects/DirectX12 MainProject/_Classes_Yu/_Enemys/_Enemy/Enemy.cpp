#include "Enemy.h"

Enemy::Enemy() {
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::NONE_OBJ_ID, Vector3::Zero, 1.0f);

	se_adjacent_ = new SoundPlayer();
	se_shooting_ = new SoundPlayer();

	state_ = nullptr;
	isHitPlayer_ = false;
}

Enemy::Enemy(Vector3 pos, float r) {
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::ENEMY, pos, r);

	se_adjacent_ = new SoundPlayer();
	se_shooting_ = new SoundPlayer();

	SwitchState(SPONE);

	forward_ = Vector3(0.0f, 0.0f, -1.0f);
	isHitPlayer_ = false;

	timeDelta_ = 0.0f;
	jumpTime_ = 0.0f;

	moveDirection_ = Vector3::Zero;
}

Enemy::~Enemy() {
	delete se_shooting_;
	delete se_adjacent_;
}

void Enemy::Initialize(const int id) {
	id_my_ = id;
	se_adjacent_->Initialize(seNameAtk.c_str(), SOUND_TYPE::SE);
	se_shooting_->Initialize(seNameBem.c_str(), SOUND_TYPE::SE, ENParams.FREQUENCY_OF_SHOOTING);  // ‚±‚±‚ÌŠÔŠu‚ÍŽËŒ‚‚Ì•p“x‚É‡‚í‚¹‚Ä
}

void Enemy::Update(const float deltaTime) {
	timeDelta_ = deltaTime;

	ObjectBase* hitObj = IsHitObject();
	isHitPlayer_ = (hitObj != nullptr) ? (hitObj->myObjectType() == OBJ_TYPE::PLAYER) : false;

	state_->Update(id_my_);
}

void Enemy::Render(DX9::SKINNEDMODEL& model) {
	model->SetPosition(pos_);
	model->SetRotation(0.0f, rotateY_, 0.0f);
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

void Enemy::Rotate(const Vector3 targetDirection) {
	forward_ = Vector3::Lerp(forward_, targetDirection, timeDelta_ * 1.0f);
	rotateY_ = -atan2f(forward_.z, forward_.x) + 4.5f;
}

Action Enemy::Move(const Vector3 targetDirection) {
	forward_ = targetDirection;
	pos_ += forward_ * ENParams.MOVE_SPEED;
	Rotate(targetDirection);
	return SUCSESS;
}

Action Enemy::Thruster() {
	return SUCSESS;
}

Action Enemy::Step(const Vector3 moveDirection) {
	const Vector2 oldPosXZ(pos_.x, pos_.z);
	moveDirection_ = moveDirection;
	jumpTime_ += timeDelta_;

	// ˆÚ“®ŒvŽZ
	pos_ += moveDirection_ * ENParams.BACKSTEP_SPEED;
	pos_.y = ENParams.BACKSTEP_INITIALVELOCITY * jumpTime_ - 0.5f * GRAVITY * jumpTime_ * jumpTime_;

	// ˆÚ“®—ÊŒvŽZ
	const Vector2 nowPosXZ(pos_.x, pos_.z);
	pos_.y = std::min(std::max(0.0f, pos_.y), 5.0f);

	const bool isFine = (pos_.y == 0.0f);

	if (isFine)
		jumpTime_ = 0.0f;

	return isFine ? SUCSESS : REPEAT;
}

Action Enemy::BackStep() {
	return Step(-forward_);
}

Action Enemy::SideStep(const Vector3 targetDirection) {
	Rotate(targetDirection);
	return Step(Vector3(forward_.z, 0.0f, forward_.x));
}

Action Enemy::Adjacent() {
	attackState_ = AttackState::Adjacent;
	se_adjacent_->PlayOneShot();
	return SUCSESS;
}

Action Enemy::Shooting() {
	attackState_ = AttackState::Shooting;
	se_shooting_->PlayRoopSE(timeDelta_);
	return SUCSESS;
}