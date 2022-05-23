/**
 * @file KeyBoadBase.h
 * @brief キーボード入力の基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

/**
 * @enum CKEY
 * 対応している文字入力
 */
enum CKEY {
	//! A～Z
	A, B, C, D, E,
	F, G, H, I, J,
	K, L, M, N, O,
	P, Q, R, S, T,
	U, V, W, X, Y, Z,
};

/**
 * @enum SKEY
 * 対応している特殊入力
*/
enum SKEY {
	//! 十字キー
	UP, DOWN, LEFT, RIGHT,

	//! その他(タブ、スペース、alt、コントロール)
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
	* @brief 指定した文字キーの入力状態を返す
	* @param inputKey 入力状態を調べたいボタン
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool OnOffKey(CKEY inputKey) {
		return (cflag_ & (1 << (int)inputKey));
	}

	/**
	* @brief 指定した特殊キーの入力状態を返す
	* @param inputKey 入力状態を調べたいボタン
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool OnOffKey(SKEY inputKey) {
		return (sflag_ & (1 << (int)inputKey));
	}

	/**
	* @brief 何かしらボタンの入力状態を返す
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool AnyKey() {
		return (cflag_ & 0xffffffff) || (sflag_ & 0xffffffff);
	}

	/**
	* @brief 入力した方向を返す
	* @return 入力された方向のベクトル
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
	//! 文字入力状態を保持する
	unsigned int cflag_;

	//! 特殊入力状態を保持する
	unsigned int sflag_;

	//! 入力した方向を保持する
	Vector2 direct_;

private:
	//! A～Zの文字数
	const int CHARA = 26;
};