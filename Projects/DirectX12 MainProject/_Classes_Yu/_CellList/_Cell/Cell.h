#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;
class ObjectBase;

// ��ԃN���X
class Cell {
public:
	Cell();
	Cell(ObjectBase* m);
	virtual ~Cell();

	static int GetIndex(int Level, int Index);  // L,I����M�����߂�

	void UpdateToMorton();		// mp_�ɍ��킹�ă��[�g���������X�V����
	void Remove();				// �o�������X�g���甲����
	ObjectBase* IsCollision();  // �Փ˔���

	// �o�������X�g(�����̑O��̋�Ԃ�����)
	Cell* prev_;
	Cell* next_;

	ObjectBase* mp_;  // �������镨��

	int level_;	    // ��ԃ��x��
	int LsIndex_;   // �e���x���ł�Index
	int MsIndex_;   // ���`�l���؂ɂ�����Index

private:
	ObjectBase* UpperSearch();		  // ��ʒT��
	ObjectBase* LowerSearch(int nr);  // ���ʒT��

	static int BitSlide(int b);  // bit��1�����炷
	static int PointToMorton(Vector2 pos);
	static void MoverToMorton(ObjectBase& m, int& L, int& I, int& M);
};