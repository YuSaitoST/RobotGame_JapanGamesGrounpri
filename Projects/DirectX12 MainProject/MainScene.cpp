//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
MainScene::MainScene()
{
	m_object_ = new ObjectManager();
}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
	m_object_->Initialize();
}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
{
	m_object_->LoadAssets();
}

// Releasing resources required for termination.
void MainScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

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
	m_object_->Update(deltaTime);

	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
	// TODO: Add your rendering code here.
	DXTK->ResetCommand();
	DXTK->ClearRenderTarget(Colors::CornflowerBlue);

	m_object_->RenderModels();

	DXTK->ExecuteCommandList();
}
