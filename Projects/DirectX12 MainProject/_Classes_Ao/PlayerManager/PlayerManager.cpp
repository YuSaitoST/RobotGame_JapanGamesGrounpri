#include "PlayerManager.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"

void PlayerManager::Initialize() {
	camera->SetView(SimpleMath::Vector3(0, 0, 0), SimpleMath::Vector3(0.35f, 0, 0));
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
	
	p_base_.Initialize(0);
	
}

void PlayerManager::LoadModel() {
	p_base_.LoadAssets(L"Player\\SwordManEX\\armor_red2_0210b.X");
}

void PlayerManager::Update(const float deltaTime) {

	camera->SetPosition(
		p_base_.GetPos().x + 3.0f,
		p_base_.GetPos().y + 5.5f,
		p_base_.GetPos().z - 7.0f
	);

	//if (Press.RotateRightCameraKey())
	//	camera->Rotate(0.0f, XMConvertToRadians(-90.0f) * deltaTime, 0.0f);
	//if (Press.RotateLeftCameraKey())
	//	camera->Rotate(0.0f, XMConvertToRadians(90.0f) * deltaTime, 0.0f);
	

	if (Press.RotateRightCameraKey()) {
		Matrix  rot = Matrix::CreateRotationY(XMConvertToRadians(180.0f * deltaTime));
		Vector3 pos = camera->GetPosition();
		pos = pos.Transform(pos, rot);
		//Matrix mat = Matrix::CreateTranslation(camera->GetPosition());
		//mat *= Matrix::CreateRotationY(XMConvertToRadians(180.0f * deltaTime));
		//Vector3 pos(mat._41, mat._42, mat._43);
		Vector3 at = p_base_.GetPos();
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}

	if (Press.RotateLeftCameraKey()) {
		float radius = camera.GetRotation().x * 3.14f / 180.0f;

		float add_x = cos(radius) * 10.0f;
		float add_z = sin(radius) * 10.0f;

		camera.GetPosition().x == 0.0f + add_x;
		camera.GetPosition().z == 0.0f + add_z;

		//camera.GetRotation().x += 10.0f;

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
}