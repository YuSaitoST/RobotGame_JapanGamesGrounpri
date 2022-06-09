#pragma once

#include "Base/dxtk.h"

namespace FieldsObjectMaterial {
    const D3DMATERIAL9 Normal{
        DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f), /* �f�B�t���[�Y�F   (�g�U��) */
        DX9::Colors::Value(0.7f, 0.7f, 0.7f, 0.6f), /* �A���r�G���g�F   (����) */
        DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f), /* �X�y�L�����F     (���ʌ�) */
        DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f), /* �G�~�b�b�V�����F (���ˌ�) */
        1.0f
    };
}