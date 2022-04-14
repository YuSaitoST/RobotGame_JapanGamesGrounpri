#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "bsCollBox.h"
#include "AttackState.h"

using namespace DirectX::SimpleMath;

class Cell;
enum OBJ_TYPE { PLAYER, ENEMY, WEAPON, NONE_OBJ_ID };

class ObjectBase {
public:
	ObjectBase();
	ObjectBase(OBJ_TYPE kind, Vector3 pos, float r);
	virtual ~ObjectBase();

	virtual void Initialize(const int id) = 0;
	virtual void LoadAssets(std::wstring file_name) = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Render(DX9::SKINNEDMODEL& model) = 0;
	virtual void UIRender() = 0;

	virtual ObjectBase* IsCollision(ObjectBase* m);  // 衝突判定(Boundingを用いたもの)

	AttackState nowAttackAttate() { return attackState_; }
	OBJ_TYPE myObjectType() { return obj_type_; }
	Vector3	 myPosition() { return pos_; }
	float	 myRadian() { return r_; }
	int		 myObjectID() { return id_my_; };

protected:
	virtual void SetMember(OBJ_TYPE kind, Vector3 pos, float r);  // メンバ変数設定
	
	void UpdateToMorton();
	ObjectBase* IsHitObject();

	OBJ_TYPE	obj_type_;		// オブジェクトの種類
	AttackState attackState_;   // 攻撃状態
	Cell*		cp_;			// 所属空間
	bsCollBox*	collision_;		// 当たり判定(sphere)
	Vector3		pos_;			// 座標
	Vector3		rotate_;		// 回転
	Vector3		forward_;       // 正面方向
	float		r_;             // 半径
	int			id_my_;			// 自分のID
};