/**
 * @file GamePadEvent.h
 * @brief �Q�[���p�b�h�̒P�����̓N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "GamePadBase.h"

class GamePadEvent final : public GamePadBase {
public:
	GamePadEvent() {}
	virtual ~GamePadEvent() {}

	virtual void Accepts(int index) override;
};