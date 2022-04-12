#include "ObjectBase.h"
#include "_Classes_Yu/_CellList/_Cell/Cell.h"

ObjectBase::ObjectBase() {
	SetMember(NONE_OBJ_ID, Vector3::Zero, 0.0f);
}

ObjectBase::ObjectBase(OBJ_TYPE kind, Vector3 pos, float r) {
	SetMember(kind, pos, r);
}

ObjectBase::~ObjectBase() {
	if (cp_ != nullptr) {
		cp_->Remove();
		delete cp_;
	}
}

void ObjectBase::SetMember(OBJ_TYPE kind, Vector3 pos, float r) {
	this->obj_type_		= kind;
	this->pos_.x		= pos.x;
	this->pos_.y		= pos.y;
	this->r_			= r;

	if (this->cp_ == nullptr)
		this->cp_		= new Cell(this);  // ���������Ԃ����蓖�Ă邽��

	this->attackState_	= AttackState::None_Attack;
	this->rotate_		= Vector3::Zero;
	this->forward_		= Vector3::Zero;
	this->collision_	= new bsCollSph();
	this->id_my_		= -1;
}

ObjectBase* ObjectBase::IsCollision(ObjectBase* m) {
	if (collision_->GetBounding().Intersects(m->collision_->GetBounding()))
		return m;

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