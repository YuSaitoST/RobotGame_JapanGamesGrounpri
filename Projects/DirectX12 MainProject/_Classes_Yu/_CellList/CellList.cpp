#include "CellList.h"

CellList::CellList() {
	cpList_				= new Cell[Cell::GetIndex(N + 1, 0)];
}

CellList::~CellList() {
	delete[] cpList_;
}

void CellList::PushList(Cell* cp) {
	int _m				= cp->MsIndex_;
	int _iMax			= Cell::GetIndex(N + 1, 0);

	assert((0 <= _m) && (_m < _iMax));

	cp->next_			= cpList_[_m].next_;		// �����̎���Cell��o�^
	cp->prev_			= &cpList_[_m];				// ������Cell�̎Q�Ƃ�o�^
	cp->next_->prev_	= cp->prev_->next_ = cp;	// �u�����̎��̑O�v�Ɓu�����̑O�̎��v�Ɏ�����Cell��o�^
}

//�Փ˔���(�w�肳�ꂽ�C���f�b�N�X�̋�ԓ��ɂ��镨�̂Ɣ���)
ObjectBase* CellList::IsCollision(int index, ObjectBase* m) {
	ObjectBase* _mp_opponent = nullptr;

	// �w�肵��index�̋�ԓ�
	for (Cell* _cp = cpList_[index].next_, *_np = nullptr;
		_cp != &cpList_[index];) {
		_np = _cp->next_;

		_mp_opponent = m->IsCollision(_cp->mp_);

		if (_mp_opponent != nullptr && m != _mp_opponent) {
			// �����肽���Ȃ��g�ݍ��킹�͂����Ŕ��ʂ���Ƃ�������
			return _mp_opponent;
		}

		_cp = _np;
	}

	return nullptr;
}