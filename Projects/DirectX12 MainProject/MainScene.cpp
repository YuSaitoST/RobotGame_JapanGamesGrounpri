//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "_Classes_Yu/_DeltaTime/DeltaTime.h"
#include "_Classes_Yu/_UI/_GameUI/_UIParamsLoad/UIParamsLoad.h"

// Initialize member variables.
MainScene::MainScene()
{
	m_object_ = new ObjectManager();
	field_ = new Fields();
}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
	UIParamsLoad::GetInstance().LoadParams();

	D3DLIGHT9 light_test_;
	light_test_.Type		= D3DLIGHT_DIRECTIONAL;
	light_test_.Diffuse		= DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light_test_.Specular	= DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light_test_.Ambient		= DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light_test_.Direction	= DX9::VectorSet(0.0f, -1.0f, 1.0f);

	Lighting.Setting("MainLight", light_test_);
	Lighting.SetEnable("MainLight", true);

	m_object_->Initialize();
	player_.Initialize();
}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
{
	descriptorHeap_ = DX12::CreateDescriptorHeap(DXTK->Device, 2);

	ResourceUploadBatch resourceUploadBatch(DXTK->Device);
	resourceUploadBatch.Begin();

	RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
	D3D12_VIEWPORT viewport = {
		0.0f, 0.0f, 1280.0f, 720.0f,
		D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
	};

	spriteBatch_ = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

	dx9GpuDescriptor_ = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap_.get(), 0);

	auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
	uploadResourcesFinished.wait();

	m_object_->LoadAssets();
	player_.LoadModel();
	field_->LoadAssets();
}

// Releasing resources required for termination.
void MainScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

	delete field_;
	delete m_object_;
}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{

}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	Press.Accepts();
	DeltaTime::Update(deltaTime);
	m_object_->Update(deltaTime);
	player_.Update(deltaTime);

	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 255, 0));  // 画面をクリア
	DXTK->Direct3D9->BeginScene();  // シーンの開始を宣言

	m_object_->RenderModels();
	
	player_.Render();
	field_->Render();


	DX9::SpriteBatch->Begin();  // スプライトの描画を開始

	player_._2D();


	DX9::SpriteBatch->End();  // スプライトの描画を終了
	DXTK->Direct3D9->EndScene();  // シーンの終了を宣言

	DXTK->Direct3D9->UpdateResource();

	DXTK->ResetCommand();
	DXTK->ClearRenderTarget(Colors::CornflowerBlue);

	const auto heapes = descriptorHeap_->Heap();
	DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

	spriteBatch_->Begin(DXTK->CommandList);

	spriteBatch_->Draw(
		dx9GpuDescriptor_,
		XMUINT2(1280, 720),   // HD
		SimpleMath::Vector2(0.0f, 0.0f)
	);

	//ui_hpGauge_->Render(spriteBatch_);

	spriteBatch_->End();

	DXTK->Direct3D9->WaitUpdate();
	DXTK->ExecuteCommandList();
}
