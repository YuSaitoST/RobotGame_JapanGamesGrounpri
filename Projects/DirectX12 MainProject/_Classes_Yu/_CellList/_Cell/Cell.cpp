#include "Cell.h"
#include "_Classes_Yu/_CellList/ObjectManager.h"

Cell::Cell() {
	level_		= -1;
	LsIndex_	= -1;
	MsIndex_	= -1;
	mp_			= nullptr;
	next_		= prev_ = this;
}

Cell::Cell(ObjectBase* m) {
	level_		= -1;
	LsIndex_	= -1;
	MsIndex_	= -1;
	mp_			= m;
	next_		= prev_ = this;
	//MoverToMorton(*mp_, level_, LsIndex_, MsIndex_);
}

Cell::~Cell() {

}

ObjectBase* Cell::UpperSearch() {
	int _m = MsIndex_;
	ObjectBase* _mr = nullptr;

	// ���[�g��Ԃ܂�
	for (int _i = (level_ - 1); 0 <= _i; _i--) {
		_m = (_m - 1) / 4;  // Index���擾

		// _m�̋�Ԃɑ΂��ďՓ˔���
		_mr = cellList.IsCollision(_m, this->mp_);
		if (_mr != nullptr)
			return _mr;
	}

	return nullptr;
}

ObjectBase* Cell::LowerSearch(int nr) {
	ObjectBase* _mr = nullptr;

	// �w�肳�ꂽIndex(nr)�̋�Ԃɑ΂��ďՓ˔���
	_mr = cellList.IsCollision(nr, this->mp_);
	if (_mr != nullptr)
		return _mr;

	// ���ʂ̍����Index (?)
	nr = nr * 4 + 1;

	// ���ʋ��4�S�ĉ��
	for (int _i = 0, _n = GetIndex(CellList::N + 1, 0); _i < 4; _i++) {
		// �ő吔�𒴂��ĂȂ���΁A�ċN���čő啪�����x���܂Ŕ���
		if (nr + _i < _n) {
			_mr = LowerSearch(nr + _i);
			if (_mr != nullptr)
				return _mr;
		}
		else {
			break;
		}
	}

	return nullptr;
}

int Cell::BitSlide(int b) {
	b = (b | b << 2) & 0x33;
	b = (b | b << 1) & 0x55;
	return b;
}

int Cell::PointToMorton(Vector2 pos) {
	// �i�q��1�ӂɂ����镪����
	const int _CN = (int)std::pow(2, CellList::N);

	// �i�q�̈�ӂ̒���
	const float _sx = 2000.0f / _CN;
	const float _sy = 2000.0f / _CN;

	// �i�q�̍��W
	const int _kx = (int)(pos.x / _sx);
	const int _ky = (int)(pos.y / _sy);

	// bit����
	const int _bx = BitSlide(_kx);
	const int _by = BitSlide(_ky);

	// OR���Z���ĕԂ�
	return (_bx | (_by << 1));
}

void Cell::MoverToMorton(ObjectBase& m, int& L, int& I, int& M) {
	// �␳
	Vector3 _pos = m.myPosition() + Vector3(1000.0f, 0.0f, 1000.0f);

	// ���O�A�E��̍��W(���_������̏ꍇ�̎�)
	Vector2 _UL = Vector2(_pos.x - m.myRadian(), _pos.z + m.myRadian());
	Vector2 _UR = Vector2(_pos.x + m.myRadian(), _pos.z - m.myRadian());

	// ���ꂼ��̃��[�g������
	int _mUL = PointToMorton(_UL);
	int _mUR = PointToMorton(_UR);

	/* 
		MortonIndex�������Ȃ�΁A
		�ő僌�x�� L = N �̂ǂꂩ�̃}�X�Ɏ��܂��Ă��邱�ƂɂȂ�
			-> ���E���܂����ł��Ȃ�
	*/
	const int _XOR = _mUL ^ _mUR;

	int _k = 0;
	// XOR��00���o�Ă���܂Ń��[�v���āA���̉��������K�ɕۑ�����
	for (int _b = _XOR; _b != 0; _b >>= 2, _k++);

	L = CellList::N - _k;  // K��L�Ƒ΂ɂȂ�l��\���A���̎����番�����x��L�����܂�
	I = _mUR >> (2 * _k);
	M = GetIndex(L, I);

	// _mUR��2*K�����E�V�t�g����
	// * _mUR���g�����R : I = _mUL^(_mUL^_mUR)>>2k ��� I = _mUR>>2K (bit���Z�̐��� a^(a^b)==b ��p���Ă���)
}

ObjectBase* Cell::IsCollision() {
	ObjectBase* _mr = nullptr;

	// �����x���T��
	_mr = cellList.IsCollision(this->MsIndex_, this->mp_);
	if (_mr != nullptr)
		return _mr;

	// ����T��
	_mr = UpperSearch();
	if (_mr != nullptr)
		return _mr;

	// �����T��
	_mr = LowerSearch(MsIndex_);
	
	return _mr;
}

//�o�������X�g���甲����
void Cell::Remove() {
	this->next_->prev_ = this->prev_;
	this->prev_->next_ = this->next_;
}

// Level,Index����MortonIndex�����߂�
int Cell::GetIndex(int Level, int Index) {
	const int _CR = (int)std::pow(4, Level);  // Common ratio (����)
	return (((_CR - 1) / (4 - 1)) + Index);  // ���䋉��
}

// mp_�ɍ��킹�ă��[�g���������X�V����
void Cell::UpdateToMorton() {
	Remove();
	MoverToMorton(*mp_, level_, LsIndex_, MsIndex_);  // ������Ԃ̍X�V
	cellList.PushList(this);
}