#include "Enemy.h"
#include "_Classes_Yu/_CellList/ObjectManager.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EneStandardParamsLoad/EneStandardParamsLoad.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EneLvParamsLoad/EneLvParamsLoad.h"
#include "_Classes_Yu/_FieldOutCheck/FieldOutCheck.h"
#include "_Classes_Yu/_CellList/_Object/WeaponBase.h"
#include "_Classes_Yu/_CellList/_Object/WeaponBase.h"
#include "DontDestroyOnLoad.h"

Enemy::Enemy(int level, Vector3 pos, float r) : level_(level), isInStep_(false), timeDelta_(0.0f), jumpTime_(0.0f) {
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::ENEMY, pos, r);
	SetMember();

	SwitchState(STANDBY);
}

Enemy::~Enemy() {
	delete meleeWapon_;
	delete m_state_;
	delete se_shooting_;
	delete se_adjacent_;
	delete se_running_;
	delete actionInterval_;
	delete hp_;
}

void Enemy::Initialize(const int id) {
	id_my_ = id;
	se_running_->Initialize(seNameRun, SOUND_TYPE::SE, 10.0f);
	se_adjacent_->Initialize(seNameAtk, SOUND_TYPE::SE, 0.5f);  // ‰¼‚Ì’lA˜A‘±UŒ‚‚È‚ç‰¹•Ï‚í‚é‚©‚à‚¾‚©‚ç‚±‚±‚ÌŽd—l‚ª•Ï‚í‚è‚»‚¤
	se_shooting_->Initialize(seNameBem, SOUND_TYPE::SE, ENParams.FREQUENCY_OF_SHOOTING);  // ‚±‚±‚ÌŠÔŠu‚ÍŽËŒ‚‚Ì•p“x‚É‡‚í‚¹‚Ä

	m_state_->Initialize(id_my_);

	forward_ = Vector3(0.0f, 0.0f, -1.0f);
}

void Enemy::LoadAssets(std::wstring file_name) {
	model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, file_name.c_str());
	model_->SetScale(0.1f);

	meleeWapon_->LoadAssets();
}

void Enemy::Update(const float deltaTime) {
	timeDelta_ = deltaTime;

	state_->Update(id_my_);
	
	Field::ClampPosition(pos_);

	UpdateToMorton();

	model_->SetPosition(pos_);
	model_->SetRotation(0.0f, rotateY_, 0.0f);

	meleeWapon_->UpdatePosition(pos_, forward_);
}

void Enemy::Render() {
	model_->Draw();
	meleeWapon_->Render();
}

void Enemy::SetMember() {
	hp_				= new HPGauge(ENLParams.HP[level_]);
	actionInterval_	= new OriTimer(ENParams.FREQUENCY_OF_SHOOTING, 0.0f);
	se_running_		= new SoundPlayer();
	se_adjacent_	= new SoundPlayer();
	se_shooting_	= new SoundPlayer();
	m_state_		= new SwitchStates();
	meleeWapon_		= new MeleeWeapon();
	attackState_	= AttackState::None_Attack;
	isHitPlayer_	= false;
	forward_		= Vector3(0.0f, 0.0f, -1.0f);
	moveDirection_	= Vector3::Zero;
	moveStartCoordinate_ = Vector3::Zero;
	lastAction_		= Action::FAILIRE;
}

void Enemy::SwitchState(ENE_STATE state) {
	state_ = m_state_->Get(state);
}

void Enemy::HitCheck() {
	ObjectBase* _obj = IsHitObject();
	if (_obj != nullptr) {
		WeaponBase* _weapon = dynamic_cast<WeaponBase*>(_obj);
		hp_->TakeDamage(_weapon->GetDamage());
		if (0 < hp_->GetHP())
			SwitchState(STAN);
		else {
			DontDestroy->score_.Addition(SCORE::BREAK_ENEMY);
			SwitchState(DOWN);
		}
	}
}

void Enemy::Rotate(const Vector3 targetDirection) {
	forward_ = Vector3::Lerp(forward_, targetDirection, timeDelta_ * 1.0f);
	rotateY_ = -atan2f(forward_.z, forward_.x) + 4.5f;
}

Action Enemy::Move(const Vector3 targetDirection) {
	if (moveStartCoordinate_ == Vector3::Zero) {
		moveStartCoordinate_ = pos_;
	}

	forward_ = targetDirection;
	pos_ += forward_ * ENLParams.SPEED_OF_ACTION[level_];
	//pos_.y = 0.0f;
	Rotate(targetDirection);
	se_running_->PlayRoopSE(timeDelta_);

	const float _moveDistance = std::fabsf((moveStartCoordinate_ - pos_).Length());

	if (25.0f <= _moveDistance) {
		moveStartCoordinate_ = Vector3::Zero;
		return SUCSESS;
	}
	else
		return REPEAT;
}

Action Enemy::Thruster() {
	return SUCSESS;
}

Action Enemy::Step(const Vector3 moveDirection) {
	if (jumpTime_ == 0.0f) {
		moveDirection_ = moveDirection;
		isInStep_ = true;
	}

	jumpTime_ += timeDelta_;

	// ˆÚ“®ŒvŽZ
	pos_ += moveDirection_ * ENLParams.SPEED_OF_STEP[level_];
	pos_.y = ENParams.STEP_INITIALVELOCITY * jumpTime_ - 0.5f * GRAVITY * jumpTime_ * jumpTime_;

	pos_.y = std::min(std::max(0.0f, pos_.y), 5.0f);

	const bool isFine = (pos_.y == 0.0f);

	if (isFine) {
		jumpTime_ = 0.0f;
		isInStep_ = false;
	}

	return isFine ? SUCSESS : REPEAT;
}

Action Enemy::Slide(const Vector3 moveDirection) {
	if (moveStartCoordinate_ == Vector3::Zero) {
		moveStartCoordinate_ = pos_;
		moveDirection_ = moveDirection;
	}

	pos_ += moveDirection_ * ENLParams.SPEED_OF_ACTION[level_];
	Rotate(XMFLOAT3(moveDirection.z, 0.0f, moveDirection.x));

	const float _moveDistance = std::fabsf((moveStartCoordinate_ - pos_).Length());

	if (8.0f <= _moveDistance) {
		moveStartCoordinate_ = Vector3::Zero;
		return SUCSESS;
	}

	return REPEAT;
}

Action Enemy::BackStep() {
	return Step(-forward_);
}

Action Enemy::SideStep(const Vector3 targetDirection) {
	return Step(XMFLOAT3(targetDirection.z, 0.0f, targetDirection.x));
}

Action Enemy::Adjacent() {
	attackState_ = AttackState::Adjacent;
	se_adjacent_->PlayRoopSE(timeDelta_);
	return SUCSESS;
}

Action Enemy::Shooting() {
	if (actionInterval_->NowTime() == 0.0f) {
		attackState_ = AttackState::Shooting;
		ObjectManager::SetShooting(id_my_, ENLParams.DAMAGE_SHO[level_], pos_, forward_, rotateY_);
		actionInterval_->ResetCountTime();
	}

	actionInterval_->Update(timeDelta_);
	se_shooting_->PlayRoopSE(timeDelta_);

	return (actionInterval_->TimeOut()) ? SUCSESS : REPEAT;
}