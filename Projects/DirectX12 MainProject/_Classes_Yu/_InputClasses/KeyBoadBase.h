/**
 * @file KeyBoadBase.h
 * @brief �L�[�{�[�h���͂̊��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

/**
 * @enum CKEY
 * �Ή����Ă��镶������
 */
enum CKEY {
	//! A�`Z
	A, B, C, D, E,
	F, G, H, I, J,
	K, L, M, N, O,
	P, Q, R, S, T,
	U, V, W, X, Y, Z,
};

/**
 * @enum SKEY
 * �Ή����Ă���������
*/
enum SKEY {
	//! �\���L�[
	UP, DOWN, LEFT, RIGHT,

	//! ���̑�(�^�u�A�X�y�[�X�Aalt�A�R���g���[��)
	TAB, SPACE, 
	LALT, RALT,
	LCTRL, RCTRL
};

class KeyBoadBase {
public:
	KeyBoadBase() : cflag_(0), sflag_(0) {}
	virtual ~KeyBoadBase() {}

	virtual void Accepts() = 0;

	/**
	* @brief �w�肵�������L�[�̓��͏�Ԃ�Ԃ�
	* @param inputKey ���͏�Ԃ𒲂ׂ����{�^��
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	inline bool OnOffKey(CKEY inputKey) {
		return (cflag_ & (1 << (int)inputKey));
	}

	/**
	* @brief �w�肵������L�[�̓��͏�Ԃ�Ԃ�
	* @param inputKey ���͏�Ԃ𒲂ׂ����{�^��
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	inline bool OnOffKey(SKEY inputKey) {
		return (sflag_ & (1 << (int)inputKey));
	}

	/**
	* @brief ��������{�^���̓��͏�Ԃ�Ԃ�
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	inline bool AnyKey() {
		return (cflag_ & 0xffffffff) || (sflag_ & 0xffffffff);
	}

	/**
	* @brief ���͂���������Ԃ�
	* @return ���͂��ꂽ�����̃x�N�g��
	*/
	inline Vector2 Direction() {
		if (sflag_ & (1 << UP   )) direct_.y = 1;
		if (sflag_ & (1 << DOWN )) direct_.y = -1;
		if (sflag_ & (1 << LEFT )) direct_.x = -1;
		if (sflag_ & (1 << RIGHT)) direct_.x = 1;
		direct_.Normalize();
		return direct_;
	}

protected:
	//! �������͏�Ԃ�ێ�����
	unsigned int cflag_;

	//! ������͏�Ԃ�ێ�����
	unsigned int sflag_;

	//! ���͂���������ێ�����
	Vector2 direct_;

private:
	//! A�`Z�̕�����
	const int CHARA = 26;
};