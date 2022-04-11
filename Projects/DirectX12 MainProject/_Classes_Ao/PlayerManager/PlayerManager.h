#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes_Yu/_InputClasses/UseKeyCheck.h"
#include "_Classes_Ao/PlayerManager/PlayerBase/PlayerBase.h"


using namespace DirectX;

class PlayerManager
{
public:
	PlayerManager(){};
	~PlayerManager(){};

	void Initialize();
	void LoadModel();

	void Update(const float deltaTime);
	void Render();

	void _2D();
	

private:
	PlayerBase p_base_;

};