#pragma once

#include "_Classes_Yu/_CellList/CellList.h"

extern CellList cellList;

class ObjectManager {
public:
	ObjectManager();
	virtual ~ObjectManager();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void RenderModels();
	void RenderSprites();

private:

};