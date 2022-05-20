/**
 * @file GamePadBase.h
 * @brief �Q�[���p�b�h���͂̊��N���X
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
 * @enum PAD
 * �Ή����Ă������
 */
enum PAD {
	//! �E����4��ނ̃{�^��
	P_A, P_B, P_X, P_Y,

	//! �\���L�[
	P_UP, P_DOWN, P_LEFT, P_RIGHT,

	//! ���X�e�B�b�N
	STICK_L_UP	, STICK_L_DOWN,
	STICK_L_LEFT, STICK_L_RIGHT,

	//! �E�X�e�B�b�N
	STICK_R_UP	, STICK_R_DOWN,
	STICK_R_LEFT, STICK_R_RIGHT,

	//! ���E�̃V�����_�[
	SHOULDER_L	, SHOULDER_R,

	//! ���E�̃g���K�[
	TRIGGER_L	, TRIGGER_R
};


class GamePadBase {
public:
	GamePadBase() : flag_(0) {};
	virtual ~GamePadBase() {}

	virtual void Accepts(int index) = 0;

	/**
	* @brief �w�肵���{�^���̓��͏�Ԃ�Ԃ�
	* @param inputKey ���͏�Ԃ𒲂ׂ����{�^��
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	inline bool OnOffKey(PAD inputKey) {
		return (flag_ & (1 << (int)inputKey));
	}

	/**
	* @brief ��������̃{�^�����͏�Ԃ�Ԃ�
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	inline bool AnyKey() {
		return (flag_ & 0xffffffff);
	}

	/**
	* @brief ���͂��ꂽ������Ԃ�
	* @return ���͂��ꂽ�����̃x�N�g��
	*/
	inline Vector2 Direction() {
		if (flag_ & (1 << P_UP   )) direct_.y = -1;
		if (flag_ & (1 << P_DOWN )) direct_.y = 1;
		if (flag_ & (1 << P_LEFT )) direct_.x = -1;
		if (flag_ & (1 << P_RIGHT)) direct_.x = 1;
		direct_.Normalize();
		return direct_;
	}
	
protected:
	//! ���͏�Ԃ��r�b�g�ŕێ�����ϐ�
	unsigned int flag_;

	//! ���͂��ꂽ������ێ�����ϐ�
	Vector2 direct_;
};