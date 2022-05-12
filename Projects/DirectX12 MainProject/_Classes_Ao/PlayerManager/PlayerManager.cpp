#include "PlayerManager.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"

void PlayerManager::Initialize() {
	camera->SetView(SimpleMath::Vector3(0, 0, 0), SimpleMath::Vector3(0, 0, 0));
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(8.0f), 16.0f / 9.0f, 1.0f, 100000.0f);
	
	p_base_.Initialize(0);

	pos_bef_ = Vector3::Zero;
	pos_aft_ = Vector3::Zero;

	
	camera_pos_ = Vector3(
		p_base_.GetPos().x + 0.0f,
		p_base_.GetPos().y + 0.0f,
		p_base_.GetPos().z - 3.0f
	);
	camera->SetPosition(camera_pos_);
}

void PlayerManager::LoadModel() {
	p_base_.LoadAssets(L"Player\\j_mein.x");

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void PlayerManager::Update(const float deltaTime) {
	
	float camera_distance_x = p_base_.GetPos().x + camera_pos_.x;
	float camera_distance_z = p_base_.GetPos().z + camera_pos_.z;

	pos_aft_ = p_base_.GetPos();

	camera_pos_ = p_base_.GetPos();


	//カメラの回転
	Vector3 at = p_base_.GetPos();
	Matrix mat = Matrix::CreateTranslation(camera->GetPosition() - at);


	if (Press.RotateRightCameraKey()) {		
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(-180.0f * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}

	if (Press.RotateLeftCameraKey()) {
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(180.0f * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}



	p_base_.Update(deltaTime);

	//移動
	p_base_.Move(deltaTime,camera);

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
		L"pos_bef_ X %f Y %f Z %f", pos_bef_.x, pos_bef_.y, pos_bef_.z
	);

	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 260.0f),
		DX9::Colors::Blue,
		L"pos_aft_ X %f Y %f Z %f", pos_aft_.x, pos_aft_.y, pos_aft_.z
	);



	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 290.0f),
		DX9::Colors::Blue,
		L"カメラ座標 X %f Y %f Z %f", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z
	);
}