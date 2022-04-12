#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
//#include "_Classes_Yu/_CellList/ObjectManager.h"  // これを入れると、コンパイルエラーが出る。おそらく循環インクルード

#define EnemyInfo EneInstructor

using namespace DirectX::SimpleMath;

class EneInstructor {
public:
	EneInstructor() {}
	virtual ~EneInstructor() {}

	//static Vector3 GetPosition(const int index) { return ObjectManager::GetEnemy(index)->myPosition(); }
};