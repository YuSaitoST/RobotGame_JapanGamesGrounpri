/**
 * @file KeyBoaState.h
 * @brief �L�[�{�[�h�̒��������̓N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "KeyBoadBase.h"

class KeyBoadState final : public KeyBoadBase {
public:
	KeyBoadState() {};
	virtual ~KeyBoadState() {};

	virtual void Accepts() override;
};