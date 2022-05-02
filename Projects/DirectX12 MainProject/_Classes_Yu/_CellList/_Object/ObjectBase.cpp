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
		this->cp_		= new Cell(this);  // 所属する空間を割り当てるため

	this->attackState_	= AttackState::None_Attack;
	this->forward_		= Vector3::Zero;
	this->rotateY_		= 0.0f;
	this->collision_	= new bsCollBox();
	this->id_my_		= -1;
}

ObjectBase* ObjectBase::IsCollision(ObjectBase* m) {
	// 同じ種類の物体同士なら衝突しない
	if ((OBJ_TYPE::WEAPON != m->myObjectType()))
		return nullptr;

	// 敵同士での衝突なら無視
	if ((id_my_ != 0) && (m->myObjectID() != 0))
		return nullptr;

	// 同じIDの物体同士では衝突しない
	if (id_my_ == m->myObjectID())
		return nullptr;

	WeaponBase* weapon = dynamic_cast<WeaponBase*>(m);

	// その武器が攻撃状態ではないなら
	if (!weapon->IsBeenAttack())
		return nullptr;

	// 衝突したら
	if (collision_->GetBounding().Intersects(weapon->collision_->GetBounding()))
		return weapon;

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