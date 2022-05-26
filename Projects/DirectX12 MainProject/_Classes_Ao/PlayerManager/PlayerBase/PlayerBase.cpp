#include "PlayerBase.h"

#include<stdio.h>
#include<cstdlib>

#include "_Classes_Yu/_FIelds/_Parameter/ConstiateParam.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "_Classes_Yu/_InputClasses/UseKeyCheck.h"
#include "_Classes_Yu/_CellList/ObjectManager.h"
#include "_Classes_Yu/_FieldOutCheck/FieldOutCheck.h"
#include "_Classes_Yu/_MeleeWeapon/MeleeWeapon.h"

#include "_Classes_Ao/PlayerManager/PlayerManager.h"


PlayerBase::PlayerBase() {
	LoadCsv();
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::PLAYER, SimpleMath::Vector3::Zero, 1.0f);

	player_model = nullptr;
	pos_ = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	//ダッシュ 関数
	boost_zero = 0;//オーバーヒートの初期値
	boost_max  = 0; //オーバーヒートの最大値
	//オーバーヒート時の変数
	overheart_flag = false; //オーバーヒートのフラグ
	overheart_time = 0.0f;//オーバーヒートしている時間 初期値
	overheart_max = 0.0f; //オーバーヒートしている時間 最大値

	//ジャンプ 関数
	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;
	//1/2
	half = 0.0f;
	//重力加速度
	gravity_ = 0.0f;
	//初速
	V0 = 0.0f;

	//近接攻撃 コンボ
	burst_state_mode = BURST_STATE::NOT_BURST;
	//一撃目
	frist_reception_time = 0.0f; //受付時間初期値
	frist_reception_max = 0.0f;  //受付時間最大値
	frist_check_flag = false;     //次に攻撃に移る
   //二撃目
	second_reception_time = 0.0f; //受付時間初期値
	second_reception_max = 0.0f;   //受付時間最大値
	second_check_flag = false;      //次に攻撃に移る
   //三撃目
	third_reception_time = 0.0f; //受付時間初期値
	third_reception_max = 0.0f;  //受付時間最大値
	third_check_flag = false;     //最後終わるまで攻撃不可

	
}

void PlayerBase::Initialize(const int id) {
	pos_ = SimpleMath::Vector3(pos_.x, 0.0f, pos_.z);
	player_spped = normal_speed;

	//ダッシュ 関数
	boost_zero = 0;     //オーバーヒートの初期値
	boost_max  = 100;   //オーバーヒートの最大値
	boost_flag = false;
	//オーバーヒート時の変数
	overheart_flag=false; //オーバーヒートのフラグ
	overheart_time=0.0f;//オーバーヒートしている時間 初期値
	overheart_max=3.0f; //オーバーヒートしている時間 最大値

	//ジャンプ 関数
	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;
	//1/2
	half = 0.5f;
	//重力加速度
	gravity_ = 3.14f;
	//初速
	V0 = 1.0f;

	//近接攻撃 コンボ
	burst_state_mode = BURST_STATE::NOT_BURST;
	//一撃目
	frist_reception_time = 0.0f; //受付時間初期値
	frist_reception_max = 1.0f;  //受付時間最大値
	frist_check_flag = false;    //次に攻撃に移る
    //二撃目
	second_reception_time = 0.0f; //受付時間初期値
	second_reception_max = 1.0f;  //受付時間最大値
	second_check_flag = false;    //次に攻撃に移る
    //三撃目
	third_reception_time = 0.0f; //受付時間初期値
	third_reception_max = 1.0f;  //受付時間最大値
	third_check_flag = false;    //最後終わるまで攻撃不可

	PlayerInfo.SetMenber(&pos_, &attackState_);
}

void PlayerBase::LoadAssets(std::wstring file_name) {
	//player_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player\\j_mein.x");
	player_model = DX9::Model::CreateFromFile(DXTK->Device9,L"Player\\j_mein.x");

	player_model->SetRotation(0.0f, XMConvertToRadians(180.0f), 0.0f);
	player_model->SetPosition(pos_);
		
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	debag_font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	time_font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void PlayerBase::LoadCsv() {
	FILE* file;

	auto a = _wfopen_s(&file, L"_Parameters\\PlayerParams.csv", L"r");
	if (a != 0)
		abort();
 	char dummy[512];
	fgets(dummy, 500, file);
	fscanf_s(file, "%f,%f,%f,%f,%i", &normal_speed, &boost_dush, &pos_.x, &pos_.z, &shotdamage);

	fclose(file);

}

void PlayerBase::Update(const float deltaTime) {
	pos_ = player_model->GetPosition();

	Field::ClampPosition(pos_);
	player_model->SetPosition(pos_);

	UpdateToMorton();
}

void PlayerBase::Setting(const float deltaTime) {
	//移動制限	
	Field::IsOut(pos_);
}

void PlayerBase::Move(const float deltaTime, DX9::CAMERA camera) {
	//キーボード操作
	if (Press.MoveForwardStateKey()) {
		Camera_Focus(camera);
		player_model->Move(0, 0, -PlayerSpeedMode() * deltaTime);
	}
	if (Press.MoveBackwardStateKey()) {
		Camera_Focus(camera);
		player_model->Move(0, 0, PlayerSpeedMode() * deltaTime);
	}
	if (Press.MoveLeftStateKey()) {
		Camera_Focus(camera);
		player_model->Move(PlayerSpeedMode() * deltaTime, 0, 0);
	}
	if (Press.MoveRightStateKey()) {
		Camera_Focus(camera);
		player_model->Move(-PlayerSpeedMode() * deltaTime, 0, 0);
	}
}

void PlayerBase::Camera_Focus(DX9::CAMERA camera) {
	Vector3 cam_dir = camera->GetForwardVector();
	cam_dir.y = 0.0f;
	cam_dir.Normalize();
	const float rotation_y = atan2(-cam_dir.z, cam_dir.x) + XMConvertToRadians(-90.0f);
	const auto  rot_mat = Matrix::CreateRotationY(rotation_y);
	player_model->SetRotationMatrix(rot_mat);
}

void PlayerBase::Dush(const float deltaTime) {
	if (!overheart_flag) {
		//ダッシュを押している間だけスピードUP
		if (DXTK->KeyState->LeftShift){//Press.DushStateKey()) {
			boost_flag = true;
			boost_max -= 1 * deltaTime;
		}
		else {
			//離したらブーストゲージ回復
			boost_flag = false;
			boost_max += 2;
		}
		if (boost_max == boost_zero) {
			boost_flag = false;
			overheart_flag = true;
		}
	}
	//オーバーヒート中
	if (overheart_flag) {
		overheart_time += deltaTime;
		if (overheart_time >= overheart_max) {
			overheart_flag = false;
			boost_max = 100;
			overheart_time = 0.0f;
		}
	}

	boost_max = std::clamp(boost_max, 0, 100);
}

float PlayerBase::PlayerSpeedMode() {
	switch (boost_flag)
	{
	case true:
		player_spped = boost_dush;
		break;
	case false:
		player_spped = normal_speed;
		break;
	}
	return player_spped;
}

//近接攻撃
void PlayerBase::Attack(const float deltaTime) {	
	switch (burst_state_mode)
	{
	case BURST_STATE::NOT_BURST:
		if (Press.AtackEventKey()) {
			burst_state_mode = BURST_STATE::FIRST;
			attackState_ = AttackState::Adjacent;
		}
		break;
	case BURST_STATE::FIRST:
		frist_reception_time += deltaTime;
		//受付時間内に攻撃ボタンを押したらフラグが立ち次の攻撃に移る
		if (frist_reception_time < frist_reception_max && 
			Press.AtackEventKey()) {
			frist_check_flag = true;
		}
		// 受付時間に押されていたら次の攻撃へ
		if (frist_reception_time >= frist_reception_max && frist_check_flag) {
			frist_reception_time = 0.0f;
			frist_check_flag = false;
			burst_state_mode = BURST_STATE::SECOND;

		}
		//受付時間に押されていなかったらリセット
		else if (frist_reception_time >= frist_reception_max && !frist_check_flag) {
			frist_reception_time = 0.0f;
			frist_check_flag = false;
			burst_state_mode = BURST_STATE::NOT_BURST;
			attackState_ = AttackState::None_Attack;
		}
		break;
	case BURST_STATE::SECOND:	
		second_reception_time += deltaTime;
		//受付時間内に攻撃ボタンを押したらフラグが立ち次の攻撃に移る
		if (second_reception_time <= second_reception_max&&
			Press.AtackEventKey()) {
			second_check_flag = true;
		}
		// 受付時間に押されていたら次の攻撃へ
		if (second_reception_time >= second_reception_max && second_check_flag) {
			second_reception_time = 0.0f;
			second_check_flag = false;
			burst_state_mode = BURST_STATE::THIRD;

		}
		//受付時間に押されていなかったらリセット
		else if (second_reception_time >= second_reception_max && !second_check_flag) {
			second_reception_time = 0.0f;
			second_check_flag = false;
			burst_state_mode = BURST_STATE::NOT_BURST;
			attackState_ = AttackState::None_Attack;
		}
		break;
	case BURST_STATE::THIRD:		
		third_reception_time += deltaTime;
		//終わり
		if (third_reception_time >= third_reception_max) {
			third_reception_time = 0.0f;
			third_reception_time = false;
			burst_state_mode = BURST_STATE::NOT_BURST;
			attackState_ = AttackState::None_Attack;
		}
		break;
	}
}

void PlayerBase::Shot(const float deltaTime) {
	if (Press.ShotEventKey()) {
		attackState_ = AttackState::Shooting;
		Vector3 flont = player_model->GetForwardVector();
		flont.y = 0.0f;
		flont.Normalize();
		ObjectManager::SetShooting(id_my_, shotdamage, pos_, -flont, rotateY_);
		attackState_ = AttackState::None_Attack;
	}
}

void PlayerBase::Jump(const float deltaTime) {
	//ジャンプ
	if (!jump_flag) {
		if (Press.JumpEventKey()) {
			jump_flag = true;
			jump_time = 0;
			jump_start_v_ = player_model->Position.y;
		}
	}
	if (jump_flag) {
		jump_time += deltaTime;
		auto pos = player_model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time - 0.5f * gravity_ * jump_time * jump_time;
		player_model->SetPosition(pos);

		if (player_model->GetPosition().y <= 0.0f) {
			player_model->SetPosition(pos.x, 0.0f, pos.z);
			jump_flag = false;
		}
	}
}

void PlayerBase::Render() {
	player_model->Draw();
}

void PlayerBase::Render(DX9::MODEL& model) {
	player_model->Draw();
}

void PlayerBase::UIRender() {
	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 0.0f),
		DX9::Colors::Red,
		L"座標　%f %f %f", pos_.x, pos_.y, pos_.z
	);
	if (burst_state_mode == BURST_STATE::NOT_BURST) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Red,
			L"連撃 0"
		);
	}
	else if (burst_state_mode == BURST_STATE::FIRST) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Red,
			L"連撃 1連撃目"
		);
		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Red,
			L"受付時間 %f", frist_reception_time
		);
	}
	else if (burst_state_mode == BURST_STATE::SECOND) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Red,
			L"連撃 2連撃目"
		);
		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Red,
			L"受付時間 %f", second_reception_time
		);
	}
	else if (burst_state_mode == BURST_STATE::THIRD) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Red,
			L"連撃 3連撃目"
		);
		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Red,
			L"受付時間 %f", third_reception_time
		);
	}
	DX9::SpriteBatch->DrawString(
		debag_font.Get(),
		SimpleMath::Vector2(0.0f, 90.0f),
		DX9::Colors::Green,
		L"ブーストゲージ %d", boost_max
	);
	DX9::SpriteBatch->DrawString(
		debag_font.Get(),
		SimpleMath::Vector2(0.0f, 120.0f),
		DX9::Colors::Red,
		L"PLAYER_Forword X %f Y %f Z %f", player_model->GetForwardVector().x, player_model->GetForwardVector().y, player_model->GetForwardVector().z
	);
}

//指定されたモーションはTRUE,それ以外はFALSE
void PlayerBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
//	for (int i = 0; i < MOTION_MAX; ++i) {
//		model->SetTrackEnable(i, FALSE);
//	}
//	model->SetTrackEnable(enableTrack, TRUE);
}