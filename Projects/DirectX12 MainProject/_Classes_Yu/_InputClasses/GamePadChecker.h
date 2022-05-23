/**
 * @file GamePadChecker.h
 * @brief �Q�[���p�b�h�̓��͂𑍊�����N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "GamePadEvent.h"
#include "GamePadState.h"


//�}�N��
#define N_PAD DXTK_GAMEPAD

class GamePadChecker {
public:
	GamePadChecker() {}
	virtual ~GamePadChecker() {}

	/**
	* @brief ���͏�Ԃ𒲂ׂ�
	* @param index �ڑ�����Ă���Q�[���p�b�h�̔ԍ�
	*/
	void Accepts(int index) {
		inpEvent_[index].Accepts(index);
		inpState_[index].Accepts(index);
	}

	/**
	* @brief �w�肵���Q�[���p�b�h�́A�w�肵���{�^���̒P�����͏�Ԃ�Ԃ�
	* @param index �Q�[���p�b�h�̔ԍ�
	* @param inputKey ���͏�Ԃ𒲂ׂ����{�^��
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool EventOnOffKey(int index, PAD inputKey) {
		return inpEvent_[index].OnOffKey(inputKey);
	}

	/**
	* @brief ��������̃{�^���̒P�����͏�Ԃ�Ԃ�
	* @param index �Q�[���p�b�h�̔ԍ�
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool EventAnyKey(int index) {
		return inpEvent_[index].AnyKey();
	}

	/**
	* @brief �\���L�[�̒P�����͂���������Ԃ�
	* @param index �Q�[���p�b�h�̔ԍ�
	* @return ���͂��ꂽ�����̃x�N�g��
	*/
	Vector2 EventDirection4(int index) {
		return inpEvent_[index].Direction();
	}

	/**
	* @brief �w�肵���{�^���̒��������͏�Ԃ�Ԃ�
	* @param indes �Q�[���p�b�h�̔ԍ�
	* @param inputKey ���͏�Ԃ𒲂ׂ����{�^��
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool StateOnOffKey(int index, PAD inputKey) {
		return inpState_[index].OnOffKey(inputKey);
	}

	/**
	* @brief ��������{�^���̒��������͏�Ԃ�Ԃ�
	* @param index �Q�[���p�b�h�̔ԍ�
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool StateAnyKey(int index) {
		return inpState_[index].AnyKey();
	}

	/**
	* @brief �\���L�[�̒��������͂���������Ԃ�
	* @param index �Q�[���p�b�h�̔ԍ�
	* @return ���͂��ꂽ������Ԃ�
	*/
	Vector2 StateDirection4(int index) {
		return inpState_[index].Direction();
	}

	/**
	* @brief ���X�e�B�b�N�̒��������͂���������Ԃ�
	* @param index �Q�[���p�b�h�̔ԍ�
	* @return ���͂��ꂽ������Ԃ�
	*/
	Vector2 LeftStateDirection360(int index) {
		return inpState_[index].LeftDirection();
	}

	/**
	* @brief �E�X�e�B�b�N�̒��������͂���������Ԃ�
	* @param index �Q�[���p�b�h�̔ԍ�
	* @return ���͂��ꂽ������Ԃ�
	*/
	Vector2 RightStateDirection360(int index) {
		return inpState_[index].RightDirection();
	}

	/**
	* @brief ���g���K�[�̓��͒l��Ԃ�
	* @param index �Q�[���p�b�h�̔ԍ�
	* @return ���͒l(0�`1)
	*/
	float LeftTrigger(int index) {
		return inpState_[index].LeftTrigger();
	}

	/**
	* @brief �E�g���K�[�̓��͒l��Ԃ�
	* @param index �Q�[���p�b�h�̔ԍ�
	* @return ���͒l(0�`1)
	*/
	float RightTrigger(int index) {
		return inpState_[index].RightTrigger();
	}

private:
	//! �Q�[���p�b�h�̒P�����͕ϐ��A�g���Q�[���p�b�h�̐��p��
	GamePadEvent inpEvent_[N_PAD];

	//!< �Q�[���p�b�h�̒��������͕ϐ��A�g���Q�[���p�b�h�̐��p��
	GamePadState inpState_[N_PAD];
};