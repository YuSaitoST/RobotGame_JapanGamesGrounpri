#include "PlayerManager.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"

void PlayerManager::Initialize() {
	camera->SetView(SimpleMath::Vector3(0, 0, 0), SimpleMath::Vector3(0, 0, 0));
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(8.0f), 16.0f / 9.0f, 1.0f, 100000.0f);

	rotate_flag = false;
	
	p_base_.Initialize(0);
	
	camera->SetPosition(
		p_base_.GetPos().x + 0.0f,
		p_base_.GetPos().y + 0.0f,
		p_base_.GetPos().z - 3.0f
	);
}

void PlayerManager::LoadModel() {
	p_base_.LoadAssets(L"Player\\j_mein.x");

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void PlayerManager::Update(const float deltaTime) {

	if (Press.RotateRightCameraKey()) {
		Vector3 at = p_base_.GetPos();
		Matrix mat = Matrix::CreateTranslation(camera->GetPosition() - at);
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(-180.0f * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);		
	}

	if (Press.RotateLeftCameraKey()) {
		Vector3 at = p_base_.GetPos();
		Matrix mat = Matrix::CreateTranslation(camera->GetPosition() - at);
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(180.0f * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}

	

	p_base_.Update(deltaTime);

	//移動
	p_base_.Move(deltaTime);

	//ダッシュ
	p_base_.Dush(deltaTime);
	
	//攻撃(近接)
	p_base_.Attack(deltaTime);

	//攻撃(射撃)
	p_base_.Shot(deltaTime);

	//ジャンプ
	p_base_.Jump(deltaTime);

	p_base_.Setting(deltaTime);
}

void PlayerManager::Render() {
	DXTK->Direct3D9->SetCamera(camera);

	p_base_.Render();
}

void PlayerManager::_2D() {
	p_base_.UIRender();

	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 230.0f),
		DX9::Colors::Blue,
		L"カメラ座標 X %f Y %f Z %f", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z
	);
}