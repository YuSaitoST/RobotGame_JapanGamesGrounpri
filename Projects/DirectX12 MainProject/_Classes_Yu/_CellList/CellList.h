#pragma once

#include "_Object/ObjectBase.h"
#include "_Cell/Cell.h"

// ��ԃ��X�g�N���X
class CellList {
public:
	static const int N = 2;  // �������x���̍ő�

public:
	CellList();
	virtual ~CellList();

	void PushList(Cell* cp);  // ���X�g�ɒǉ�
	ObjectBase* IsCollision(int index, ObjectBase* m);  // �Փ˔���	

private:
	Cell* cpList_;  // ���`��ԃ��X�g(Cell���܂Ƃ߂�List)
};