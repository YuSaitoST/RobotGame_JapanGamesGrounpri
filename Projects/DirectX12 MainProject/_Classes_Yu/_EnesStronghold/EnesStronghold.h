#pragma once

#include "_Classes_Yu/_CellList/_Object/ObjectBase.h"

class EnesStronghold final : public ObjectBase {
public:
	EnesStronghold();
	virtual ~EnesStronghold() {}

	virtual void Initialize(const int id) {};
	virtual void LoadAssets();
	virtual void LoadAssets(std::wstring file_name) {};
	virtual void Update(const float deltaTime);
	virtual void Render();
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender() {};

private:
	DX9::MODEL mod_base_;
};