/**
 * @file LoadCSC.h
 * @brief CSV読み取り処理
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
//#include <string>
#include "Base/pch.h"

namespace CSV {
	void Schan(std::wstring fileName, const char* format, ...);
	void Schan(std::wstring fileName, int& numberOfData, std::vector<DirectX::XMFLOAT3>& positionList);
	void Split(std::string& param, int& numberOfData);
	DirectX::XMFLOAT3 Split(std::string& param);
}