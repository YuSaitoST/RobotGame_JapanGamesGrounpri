/**
 * @file KeyBoadChecker.h
 * @brief �L�[�{�[�h�̓��͂𑍊�����N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "KeyBoadEvent.h"
#include "KeyBoadState.h"

class KeyBoadChecker {
public:
	KeyBoadChecker() {}
	virtual ~KeyBoadChecker() {}

	/**
	* @brief ���͏�Ԃ𒲂ׂ�
	*/
	void Accepts(){
		inpEvent_.Accepts();
		inpState_.Accepts();
	}

	/**
	* @brief �w�肵�������L�[�̒P�����͏�Ԃ�Ԃ�
	* @param inputKey ���͏�Ԃ𒲂ׂ����{�^��
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool EventOnOffKey(CKEY inputKey){
		return inpEvent_.OnOffKey(inputKey);
	}

	/**
	* @brief �w�肵������L�[�̒P�����͏�Ԃ�Ԃ�
	* @param inputKey ���͏�Ԃ𒲂ׂ����{�^��
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool EventOnOffKey(SKEY inputKey) {
		return inpEvent_.OnOffKey(inputKey);
	}

	/**
	* @brief ��������{�^���̒P�����͏�Ԃ�Ԃ�
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool EventAnyKey(){
		return inpEvent_.AnyKey();
	}

	/**
	* @brief �P�����͂���������Ԃ�
	* @return ���͂��ꂽ�����̃x�N�g��
	*/
	Vector2 EventDirection(){
		return inpEvent_.Direction();
	}
	
	/**
	* @brief �w�肵�������L�[�̒��������͏�Ԃ�Ԃ�
	* @param inputKey ���͏�Ԃ𒲂ׂ����{�^��
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool StateOnOffKey(CKEY inputKey){
		return inpState_.OnOffKey(inputKey);
	}

	/**
	* @brief �w�肵������L�[�̒��������͏�Ԃ�Ԃ�
	* @param inputKey ���͏�Ԃ𒲂ׂ����{�^��
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool StateOnOffKey(SKEY inputKey) {
		return inpState_.OnOffKey(inputKey);
	}

	/**
	* @brief ��������{�^���̒��������͏�Ԃ�Ԃ�
	* @return ���͂���Ă����true�@�Ȃ����false
	*/
	bool StateAnyKey(){
		return inpState_.AnyKey();
	}

	/**
	* @brief ���������͂���������Ԃ�
	* @return ���͂��ꂽ�����̃x�N�g��
	*/
	Vector2 StateDirection(){
		return inpState_.Direction();
	}

private:
	//! �L�[�{�[�h�̒P�����͕ϐ�
	KeyBoadEvent inpEvent_;

	//! �L�[�{�[�h�̒��������͕ϐ�
	KeyBoadState inpState_;
};