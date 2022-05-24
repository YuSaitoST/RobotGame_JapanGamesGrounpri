#include "PlayerManager.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"

void PlayerManager::Initialize() {
	p_base_.Initialize(0);
	
}

void PlayerManager::LoadModel() {
	p_base_.LoadAssets(L"Player\\j_mein.x");

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	//camera->SetView(SimpleMath::Vector3(0, 0, 0), SimpleMath::Vector3(0, 0, 0));

	//camera_pos_ = Vector3(
	//	p_base_.GetPos().x + 0.11f,
	//	p_base_.GetPos().y + 0.15f,
	//	p_base_.GetPos().z - 1.17f
	//);


	//camera->SetPosition(camera_pos_);
	//camera->Rotate(0.0f, -0.3f, 0.0f);

	camera_pos_ = Vector3(
		p_base_.GetPos().x + 0.6f,
		p_base_.GetPos().y + 0.19f,
		p_base_.GetPos().z - 1.6f
	);

	Vector3 at = Vector3(p_base_.GetPos().x + 0.08f, p_base_.GetPos().y + 0.15f, p_base_.GetPos().z);

	camera->SetViewLookAt(camera_pos_, at, Vector3::Up);//p_base_.GetPos(), Vector3::Up);
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(20.0f), 16.0f / 9.0f, 1.0f, 100000.0f);
}

void PlayerManager::Update(const float deltaTime) {
	
	pos_bef_ = p_base_.GetPos();

	//カメラの回転
	Vector3 at = Vector3(p_base_.GetPos().x + 0.08f, p_base_.GetPos().y + 0.15f, p_base_.GetPos().z);
	Matrix mat = Matrix::CreateTranslation(camera->GetPosition() - at);

	

	if (Press.RotateLeftCameraKey()) {		
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(-180.0f * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}

	if (Press.RotateRightCameraKey()) {
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(180.0f * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}


	p_base_.Update(deltaTime);

	//移動
	p_base_.Move(deltaTime, camera);


	pos_aft_ = p_base_.GetPos();

	pos_distance_ = pos_aft_ - pos_bef_;

	camera->SetPosition(camera->GetPosition() + pos_distance_);


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
		DX9::Colors::Red,
		L"カメラ座標 X %f Y %f Z %f", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z
	);

	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 260.0f),
		DX9::Colors::Red,
		L"pos_bef_ X %f Y %f Z %f", pos_bef_.x, pos_bef_.y, pos_bef_.z
	);

	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 290.0f),
		DX9::Colors::Red,
		L"pos_aft_ X %f Y %f Z %f", pos_aft_.x, pos_aft_.y, pos_aft_.z
	);

	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 320.0f),
		DX9::Colors::Red,
		L"pos_distance_ X %f Y %f Z %f", pos_distance_.x, pos_distance_.y, pos_distance_.z
	);


	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 350.0f),
		DX9::Colors::Red,
		L"CAMERA   GetForwardVector X %f Y %f Z %f", camera->GetForwardVector().x, camera->GetForwardVector().y, camera->GetForwardVector().z
	);


}