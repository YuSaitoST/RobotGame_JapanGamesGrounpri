//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include "_Classes_Yu/_MainLight/MainLight.h"
#include "_Classes_Yu/_InputClasses/UseKeyCheck.h"
#include "_Classes_Yu/_CellList/ObjectManager.h"
#include "_Classes_Yu/_FIelds/Fields.h"

#include "_Classes_Yu/_UI/_GameUI/_MSHPGauge/MSHPGauge.h"
#include "_Classes_Yu/_UI/_GameUI/_MiniMap/MiniMap.h"

#include "_Classes_Ao/PlayerManager/PlayerManager.h"
#include"_Classes_Ao/CameraManager/CameraManager.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class MainScene final : public Scene {
public:
	MainScene();
	virtual ~MainScene() { Terminate(); }

	MainScene(MainScene&&) = default;
	MainScene& operator= (MainScene&&) = default;

	MainScene(MainScene const&) = delete;
	MainScene& operator= (MainScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
	DX12::DESCRIPTORHEAP descriptorHeap_;
	DX12::SPRITEBATCH    spriteBatch_;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor_;

	ObjectManager* m_object_;
	CameraManager* camera_;

	PlayerManager player_;

	Fields* field_;

	MSHPGauge* ui_hpGauge_;
	MiniMap* ui_miniMap_;
};