/**
 * @file KeyBoadEvent.h
 * @brief �L�[�{�[�h�̒P�����̓N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "KeyBoadBase.h"

class KeyBoadEvent final : public KeyBoadBase {
public:
	KeyBoadEvent() {};
	virtual ~KeyBoadEvent() {};

	virtual void Accepts() override;
};