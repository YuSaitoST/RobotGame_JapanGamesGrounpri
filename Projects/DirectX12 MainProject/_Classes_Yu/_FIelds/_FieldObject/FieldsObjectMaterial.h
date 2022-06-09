#pragma once

#include "Base/dxtk.h"

namespace FieldsObjectMaterial {
    const D3DMATERIAL9 Normal{
        DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f), /* ディフューズ色   (拡散光) */
        DX9::Colors::Value(0.7f, 0.7f, 0.7f, 0.6f), /* アンビエント色   (環境光) */
        DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f), /* スペキュラ色     (鏡面光) */
        DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f), /* エミッッション色 (放射光) */
        1.0f
    };
}