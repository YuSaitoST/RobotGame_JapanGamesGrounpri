#include "Enemy.h"
#include "_Classes_Yu/_CellList/ObjectManager.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EneStandardParamsLoad/EneStandardParamsLoad.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/_EneLvParamsLoad/EneLvParamsLoad.h"
#include "_Classes_Yu/_FieldOutCheck/FieldOutCheck.h"
#include "_Classes_Yu/_CellList/_Object/WeaponBase.h"
#include "DontDestroyOnLoad.h"

Enemy::Enemy(int level, Vector3 pos, float r) : level_(level), isInStep_(false), timeDelta_(0.0f), jumpTime_(0.0f) {
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::ENEMY, pos, r);
	SetMember();

	SwitchState(ENE_STATE::STANDBY);

	actionCount_ = 0;

	shoulderL_ = new MSShoulderSide();
}

Enemy::~Enemy() {
	delete shoulderL_;
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
	se_running_->Initialize(L"_Sounds\\_SE\\SELab_RunningOnAsphalt1.wav", SOUND_TYPE::SE, 10.0f);
	se_adjacent_->Initialize(L"_Sounds\\_SE\\_Attack\\SELab_useOnesSword1.wav", SOUND_TYPE::SE, 0.5f);  // ���̒l�A�A���U���Ȃ特�ς�邩�������炱���̎d�l���ς�肻��
	se_shooting_->Initialize(L"_Sounds\\_SE\\_Attack\\SELab_beamCannon1.wav", SOUND_TYPE::SE, ENParams.FREQUENCY_OF_SHOOTING);  // �����̊Ԋu�͎ˌ��̕p�x�ɍ��킹��

	m_state_->Initialize(id_my_);
	meleeWapon_->Initialize(id_my_);

	forward_ = Vector3(0.0f, 0.0f, -1.0f);
}

void Enemy::LoadAssets(std::wstring file_name) {
	//model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, file_name.c_str());
	model_ = DX9::Model::CreateFromFile(DXTK->Device9, file_name.c_str());
	//const float size = 0.2032f * 50.0f;
	//model_->SetScale(size);
	model_->SetScale(1.0f);

	meleeWapon_->LoadAssets();

	shoulderL_->LoadAsset(L"Player\\L_sholder.x");
}

void Enemy::Update(const float deltaTime) {
	timeDelta_ = deltaTime;

	state_->Update(id_my_);
	
	Field::ClampPosition(pos_);

	UpdateToMorton();

	model_->SetPosition(pos_);
	model_->SetRotation(0.0f, rotateY_, 0.0f);

	//meleeWapon_->UpdatePosition(pos_, forward_);
}

void Enemy::Render() {
	////���C�g�̕����x�N�g��
	//XMFLOAT3 lightDir = XMFLOAT3(0.0f, -1.0f, 0.0f);

	////�n��
	//Plane plane = Plane(0, 1, 0, 1);

	////�V���h�E�̃}�g���N�X
	//SimpleMath::Matrix matrix = SimpleMath::Matrix::CreateShadow(lightDir, plane);
	//
	////���f���̃}�g���N�X
	//DirectX::XMMATRIX enemy = model_->GetWorldTransform();

	////����
	//DirectX::XMMATRIX W = (DirectX::XMMATRIX)matrix;
	//model_->SetRotationMatrix(W);
	//model_->SetScale(1.0f);
	////DXTK->Device9->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&W);

	////alpha blend the shadow
	//DXTK->Device9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);				// TRUE ���w�肷��ƁA�A���t�@�u�����h�̓����x���L���ɂȂ�܂��B�f�t�H���g�l�� FALSE �ł��B
	//DXTK->Device9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// �Z / �u�����h�W���� (As, As, As, As)�B
	//DXTK->Device9->SetRenderState(D3DRS_DESTBLEND, D3DPBLENDCAPS_INVSRCALPHA);

	////�A�̃}�e���A����p��
	//D3DMATERIAL9 material;
	//material.Diffuse = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.5f);
	//material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 1.0f);
	//material.Emissive = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 1.0f);
	//material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 1.0f);

	////�[�x�o�b�t�@�𖳌��ɂ���(���̏�ɉe��`�悷��ۂ�Z�t�@�C�g���������Ȃ��悤�ɂ���)
	//DXTK->Device9->SetRenderState(D3DRS_ZENABLE, false);
	//DXTK->Device9->SetMaterial(&material);

	//meleeWapon_->Render();

	model_->Draw();
	shoulderL_->Render(pos_, XMFLOAT3(-forward_.z, 0.0f, forward_.x));

	//DXTK->Device9->SetRenderState(D3DRS_ZENABLE, true);				// �[���o�b�t�@�����O��ԁB
	//DXTK->Device9->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//DXTK->Device9->SetRenderState(D3DRS_STENCILENABLE, false);
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
	posListID_ = -1;
}

void Enemy::SwitchState(ENE_STATE state) {
	state_ = m_state_->Get(state);
}

void Enemy::HitCheck() {
	ObjectBase* _obj = IsHitObject();

	if (_obj == nullptr)
		return;

	WeaponBase* _weapon = dynamic_cast<WeaponBase*>(_obj);
	hp_->TakeDamage(_weapon->GetDamage());
	SwitchState(STATE_OF_DAMAGE[(int)(0 < hp_->GetHP())]);
}

void Enemy::Rotate(const Vector3 targetDirection) {
	forward_ = Vector3::Lerp(forward_, targetDirection, timeDelta_ * 1.0f);
	rotateY_ = -atan2f(forward_.z, forward_.x) + 4.5f;
}

Action Enemy::Move(const Vector3 targetDirection) {
	// �����ݒ�
	if (moveStartCoordinate_ == Vector3::Zero) {
		attackState_ = AttackState::None_Attack;
		moveStartCoordinate_ = pos_;
		forward_ = targetDirection;
		Rotate(targetDirection);
	}

	pos_ += forward_ * ENLParams.SPEED_OF_ACTION[level_];
	pos_.y = 0.0f;  // �󒆂Ɉړ�����̂�h������
	se_running_->PlayRoopSE(timeDelta_);

	const float _moveDistance = std::fabsf((moveStartCoordinate_ - pos_).Length());

	if (1.0f <= _moveDistance) {
		moveStartCoordinate_ = Vector3::Zero;
		actionCount_ += 1;
		return SUCSESS;
	}
	else
		return REPEAT;

	return SUCSESS;
}

Action Enemy::Step(const Vector3 moveDirection) {
	// �����ݒ�
	if (jumpTime_ == 0.0f) {
		Rotate(PlayerInfo.GetDirection(myPosition()));
		attackState_ = AttackState::None_Attack;
		moveDirection_ = moveDirection;
		isInStep_ = true;
	}

	jumpTime_ += timeDelta_;

	// �ړ��v�Z
	pos_ += moveDirection_ * ENLParams.SPEED_OF_ACTION[level_];
	pos_.y = ENParams.STEP_INITIALVELOCITY * jumpTime_ - 0.5f * GRAVITY * jumpTime_ * jumpTime_;
	pos_.y = std::max(0.0f, pos_.y);

	const bool isFine = (pos_.y == 0.0f);

	if (isFine) {
		jumpTime_ = 0.0f;
		isInStep_ = false;
		actionCount_ += 1;
		return SUCSESS;
	}

	return REPEAT;
}

Action Enemy::Slide(const Vector3 moveDirection) {
	// �����ݒ�
	if (moveStartCoordinate_ == Vector3::Zero) {
		moveStartCoordinate_ = pos_;
		moveDirection_ = moveDirection;
	}

	pos_ += moveDirection_ * ENLParams.SPEED_OF_ACTION[level_];
	Rotate(XMFLOAT3(moveDirection.z, 0.0f, moveDirection.x));

	const float _moveDistance = std::fabsf((moveStartCoordinate_ - pos_).Length());

	// �ړ��ʂ����ȏ�ɂȂ�����I��
	if (1.0f <= _moveDistance) {
		moveStartCoordinate_ = Vector3::Zero;
		actionCount_ += 1;
		return SUCSESS;
	}

	return REPEAT;
}

Action Enemy::BackStep() {
	if (actionCount_ = 0)
		return Step(-forward_);
	else if (actionCount_ = 1)
		return Slide(-forward_);
	else if (actionCount_ == 2)
		return Stay();
	else {
		actionCount_ = 0;
		return SUCSESS;
	}
}

Action Enemy::SideStep(const Vector3 targetDirection) {
	if (actionCount_ == 0)
		Step(XMFLOAT3(targetDirection.z, 0.0f, targetDirection.x));
	else if (actionCount_ == 1)
		Slide(XMFLOAT3(targetDirection.z, 0.0f, targetDirection.x));
	else if (actionCount_ == 2)
		Stay();
	else {
		actionCount_ = 0;
		return SUCSESS;
	}
}

Action Enemy::Stay() {
	// �����ݒ�
	if (actionInterval_->NowTime() == 0.0f) {
		actionInterval_->ResetCountTime();
	}

	actionInterval_->Update(timeDelta_);

	if (actionInterval_->TimeOut()) {
		actionCount_ = 0;
		return SUCSESS;
	}
	else
		return REPEAT;
}

Action Enemy::Adjacent() {
	// �����ݒ�
	if (actionInterval_->NowTime() == 0.0f) {
		actionInterval_->ResetCountTime();
		attackState_ = AttackState::Adjacent;
	}

	actionInterval_->Update(timeDelta_);
	se_adjacent_->PlayRoopSE(timeDelta_);

	return (actionInterval_->TimeOut()) ? SUCSESS : REPEAT;
}

Action Enemy::Shooting() {
	// �����ݒ�
	if (actionInterval_->NowTime() == 0.0f) {
		actionInterval_->ResetCountTime();
		attackState_ = AttackState::Shooting;
		ObjectManager::SetShooting(id_my_, ENLParams.DAMAGE_SHO[level_], pos_, forward_, rotateY_);
	}

	actionInterval_->Update(timeDelta_);
	se_shooting_->PlayRoopSE(timeDelta_);

	return (actionInterval_->TimeOut()) ? SUCSESS : REPEAT;
}