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
	this->obj_type_ = kind;
	this->pos_.x = pos.x;
	this->pos_.y = pos.y;
	if (this->cp_ == nullptr)
		this->cp_ = new Cell(this);  // 所属する空間を割り当てるため

	rotate_ = Vector3::Zero;
	forward_ = Vector3::Zero;
	collision_ = new bsCollSph();
}

ObjectBase* ObjectBase::IsCollision(ObjectBase* m) {
	if (collision_->GetBounding().Intersects(m->collision_->GetBounding()))
		return m;

	return nullptr;
}

void ObjectBase::UpdateToMorton() {
	// 存在するなら、所属空間の更新をする
	if (cp_ != nullptr)
		cp_->UpdateToMorton();
}

ObjectBase* ObjectBase::IsHitObject() {
	return cp_->IsCollision();  // 上方、同レベル、下方の3方向を調べる(四分木探索)
}