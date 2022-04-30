#include "ObjectBase.h"
#include "_Classes_Yu/_CellList/_Cell/Cell.h"
#include "_Classes_Yu/_CellList/_Object/WeaponBase.h"

ObjectBase::ObjectBase() {
	SetBaseMember(NONE_OBJ_ID, Vector3::Zero, 0.0f);
}

ObjectBase::ObjectBase(OBJ_TYPE kind, Vector3 pos, float r) {
	SetBaseMember(kind, pos, r);
}

ObjectBase::~ObjectBase() {
	if (cp_ != nullptr) {
		cp_->Remove();
		delete cp_;
	}
}

void ObjectBase::SetBaseMember(OBJ_TYPE kind, Vector3 pos, float r) {
	this->obj_type_		= kind;
	this->pos_			= pos;
	this->r_			= r;

	if (this->cp_ == nullptr)
		this->cp_		= new Cell(this);  // ���������Ԃ����蓖�Ă邽��

	this->attackState_	= AttackState::None_Attack;
	this->forward_		= Vector3::Zero;
	this->rotateY_		= 0.0f;
	this->collision_	= new bsCollBox();
	this->id_my_		= -1;
}

ObjectBase* ObjectBase::IsCollision(ObjectBase* m) {
	// ������ނ̕��̓��m�Ȃ�Փ˂��Ȃ�
	if ((OBJ_TYPE::WEAPON != m->myObjectType()))
		return nullptr;

	// �G���m�ł̏Փ˂Ȃ疳��
	if ((id_my_ != 0) && (m->myObjectID() != 0))
		return nullptr;

	// ����ID�̕��̓��m�ł͏Փ˂��Ȃ�
	if (id_my_ == m->myObjectID())
		return nullptr;

	WeaponBase* weapon = dynamic_cast<WeaponBase*>(m);

	// ���̕��킪�U����Ԃł͂Ȃ��Ȃ�
	if (!weapon->IsBeenAttack())
		return nullptr;

	// �Փ˂�����
	if (collision_->GetBounding().Intersects(weapon->collision_->GetBounding()))
		return weapon;

	return nullptr;
}

void ObjectBase::UpdateToMorton() {
	// ���݂���Ȃ�A������Ԃ̍X�V������
	if (cp_ != nullptr)
		cp_->UpdateToMorton();
}

ObjectBase* ObjectBase::IsHitObject() {
	return cp_->IsCollision();  // ����A�����x���A������3�����𒲂ׂ�(�l���ؒT��)
}