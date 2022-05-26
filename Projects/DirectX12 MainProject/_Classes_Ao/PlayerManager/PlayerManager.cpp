#include "PlayerManager.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"

void PlayerManager::Initialize() {
	p_base_.Initialize(0);
	
}

void PlayerManager::LoadModel() {
	p_base_.LoadAssets(L"Player\\j_mein.x");

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);


	camera_pos_ = Vector3(
		p_base_.GetPos().x + 0.3f,
		p_base_.GetPos().y + 0.20f,
		p_base_.GetPos().z - 1.6f
	);

	Vector3 at = Vector3(p_base_.GetPos().x + 0.08f, p_base_.GetPos().y + 0.15f, p_base_.GetPos().z);

	camera->SetViewLookAt(camera_pos_, at, Vector3::Up);//p_base_.GetPos(), Vector3::Up);
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(20.0f), 16.0f / 9.0f, 1.0f, 100000.0f);
}

void PlayerManager::Update(const float deltaTime) {

	pos_bef_ = p_base_.GetPos();

	//ƒJƒƒ‰‚Ì‰ñ“]
	Vector3 at = Vector3(p_base_.GetPos().x + 0.08f, p_base_.GetPos().y + 0.15f, p_base_.GetPos().z);
	Matrix mat = Matrix::CreateTranslation(camera->GetPosition() - at);

	float camera_rotate = p_base_.GetCameraRotate();

	if (Press.RotateLeftCameraKey()) {
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(camera_rotate * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}

	if (Press.RotateRightCameraKey()) {
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(-camera_rotate * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}


	p_base_.Update(deltaTime);

	//ˆÚ“®
	p_base_.Move(deltaTime, camera);


	pos_aft_ = p_base_.GetPos();

	pos_distance_ = pos_aft_ - pos_bef_;

	camera->SetPosition(camera->GetPosition() + pos_distance_);


	//ƒ_ƒbƒVƒ…
	p_base_.Dush(deltaTime);

	//UŒ‚(‹ßÚ)
	p_base_.Attack(deltaTime);

	//UŒ‚(ËŒ‚)
	p_base_.Shot(deltaTime);

	//ƒWƒƒƒ“ƒv
	p_base_.Jump(deltaTime);

	p_base_.Setting(deltaTime);


}

void PlayerManager::Render() {
	DXTK->Direct3D9->SetCamera(camera);

	p_base_.Render();
}

void PlayerManager::_2D() {
	p_base_.UIRender();
}