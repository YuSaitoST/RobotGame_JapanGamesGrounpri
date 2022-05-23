/**
 * @file GamePadState.h
 * @brief �Q�[���p�b�h�̒��������̓N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "GamePadBase.h"

class GamePadState final : public GamePadBase {
public:
	GamePadState() :direct_L_(Vector2::Zero), direct_R_(Vector2::Zero), n_Ltrg_(0), n_Rtrg_(0) {};
	virtual ~GamePadState() {}

	virtual void Accepts(int index) override;

	/**
	* @brief ���X�e�B�b�N�̓��͕�����Ԃ�
	* @return ���͂��ꂽ�����̃x�N�g��
	*/
	Vector2 LeftDirection() {
		direct_L_.Normalize();
		return direct_L_;
	}

	/**
	* @brief �E�X�e�B�b�N�̓��͕�����Ԃ�
	* @return ���͂��ꂽ�����̃x�N�g��
	*/
	Vector2 RightDirection() {
		direct_R_.Normalize();
		return direct_R_; 
	}

	/**
	* @brief ���g���K�[�̓��͒l��Ԃ�
	* @return ���͒l(0�`1)
	*/
	float LeftTrigger() { 
		return n_Ltrg_; 
	}

	/**
	* @brief �E�g���K�[�̓��͒l��Ԃ�
	* @return ���͒l(0�`1)
	*/
	float RightTrigger() {
		return n_Rtrg_;
	}

private:
	Vector2 direct_L_;		//!< ���X�e�B�b�N�̓��͕���
	Vector2 direct_R_;		//!< �E�X�e�B�b�N�̓��͕���
	float n_Ltrg_, n_Rtrg_;	//!< �g���K�[�̓��͒l
};