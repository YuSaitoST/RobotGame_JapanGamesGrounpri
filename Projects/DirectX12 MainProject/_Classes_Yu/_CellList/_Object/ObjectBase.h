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

	virtual ObjectBase* IsCollision(ObjectBase* m);  // �Փ˔���(Bounding��p��������)

	AttackState nowAttackAttate() { return attackState_; }
	OBJ_TYPE myObjectType() { return obj_type_; }
	Vector3	 myPosition() { return pos_; }
	float	 myRadian() { return r_; }
	int		 myObjectID() { return id_my_; };

protected:
	virtual void SetMember(OBJ_TYPE kind, Vector3 pos, float r);  // �����o�ϐ��ݒ�
	
	void UpdateToMorton();
	ObjectBase* IsHitObject();

	OBJ_TYPE	obj_type_;		// �I�u�W�F�N�g�̎��
	AttackState attackState_;   // �U�����
	Cell*		cp_;			// �������
	bsCollBox*	collision_;		// �����蔻��(sphere)
	Vector3		pos_;			// ���W
	Vector3		rotate_;		// ��]
	Vector3		forward_;       // ���ʕ���
	float		r_;             // ���a
	int			id_my_;			// ������ID
};