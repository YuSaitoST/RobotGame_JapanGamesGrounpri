#include "_Camera.h"

#include "_Classes_Yu/_LoadCSV/LoadCSV.h"

_Camera::_Camera() {
	LoadCSV();

	camera_pos_   = SimpleMath::Vector3::Zero;
	pos_bef_      = SimpleMath::Vector3::Zero;
	pos_aft_      = SimpleMath::Vector3::Zero;
	pos_distance_ = SimpleMath::Vector3::Zero;

}

void _Camera::LoadCSV() {
	CSV::Schan(
		L"_Parameters\\CameraParams.csv",
		"%f",
		&camera_rotate_speed
	);
}

 void _Camera::LoadAssets(SimpleMath::Vector3 pos) {

	camera_pos_ = Vector3(
		pos.x + 0.0f,
		pos.y + 0.3f,
		pos.z - 1.17f
	);

	Vector3 at = Vector3(pos.x, pos.y + 0.15f, pos.z);

	camera->SetViewLookAt(camera_pos_, at, Vector3::Up);
	camera->SetPerspectiveFieldOfView(XMConvertToRadians(20.0f), 16.0f / 9.0f, 1.0f, 100000.0f);

}

void _Camera::Update(const float deltaTime, SimpleMath::Vector3 pos) {

	pos_bef_ = pos;

	//ƒJƒƒ‰‚Ì‰ñ“]
	Vector3 at = Vector3(pos.x, pos.y + 0.15f, pos.z);
	Matrix mat = Matrix::CreateTranslation(camera->GetPosition() - at);

	float camera_rotate = camera_rotate_speed;


	if (Press.RotateLeftCameraKey()) {
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(-camera_rotate * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}

	if (Press.RotateRightCameraKey()) {
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(camera_rotate * deltaTime));
		mat *= rot;
		Vector3 pos(mat._41, mat._42, mat._43);
		pos += at;
		camera->SetViewLookAt(pos, at, Vector3::Up);
	}


}

void _Camera::Setting(SimpleMath::Vector3 pos) {
	pos_aft_ = pos;

	pos_distance_ = pos_aft_ - pos_bef_;

	camera->SetPosition(camera->GetPosition() + pos_distance_);
}

void _Camera::Render() {
	DXTK->Direct3D9->SetCamera(camera);

}