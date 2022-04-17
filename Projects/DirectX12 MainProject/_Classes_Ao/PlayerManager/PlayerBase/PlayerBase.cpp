#include "PlayerBase.h"

#include<stdio.h>
#include<cstdlib>


PlayerBase::PlayerBase() {
	player_model = nullptr;
	player_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	speed = 0.0f;

	//ジャンプ 関数
	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;

}

void PlayerBase::Initialize() {
	player_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	jump_flag = false;
	speed = 60.0f;

	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;

}


void PlayerBase::LoadModel() {
	player_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player\\SwordManEX\\armor_red2_0210b.X");
	player_model->SetScale(0.1f);
	
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

}
void PlayerBase::LoadEffect() {

}

void LoadCsv() {
	FILE* file;  // csv入れる変数
 /*
	_wfopen_sでファイルを開く、L"r"は開き方の指定(今回は読み込み)
	変数に代入するのは、読み込めたかのチェックのため
 */

	auto a = _wfopen_s(&file, L"", L"r");
	if (a == 0);// ファイルが開けない場合例外で落とす
 // * assertだとデバッグ時にしか機能しないため、abort()かretun exceptionの方がよき

 // PLや他のPGになんの値か説明する部分を読み込む(ローカル変数に入れるだけ)
	char dummy[512];
	fgets(dummy, 500, file);

	/*
   本命の値代入、%iはint型、%fはfloat型、%sはstring型
   その後に、.hで定義した変数の参照を渡す
	*/
	//fscanf_s(file, "%i,%f,%s", &interger, &floatnum, &str);

	// ファイルを閉じる
	fclose(file);

}

void PlayerBase::Setting() {
	player_model->SetRotation(0.0f, XMConvertToRadians(180.0f), 0.0f);
	player_pos = player_model->GetPosition();

	//移動制限
	player_pos.x = std::min(std::max(player_pos.x, 0.0f),  200.0f);
	player_pos.y = std::min(std::max(player_pos.y, 0.0f), 10000.0f);
	player_pos.z = std::min(std::max(player_pos.z, 0.0f),  200.0f);


}

void PlayerBase::Move_Front(const float deltaTime) {
	player_model->Move(0.0f, 0.0f, -speed * deltaTime);
}

void PlayerBase::Move_Back(const float deltaTime) {
	player_model->Move(0.0f, 0.0f, speed * deltaTime);
}

void PlayerBase::Move_Right(const float deltaTime) {
	player_model->Move(-speed * deltaTime, 0.0f, 0.0f);
}

void PlayerBase::Move_Left(const float deltaTime) {
	player_model->Move(speed * deltaTime, 0.0f, 0.0f);
}

void PlayerBase::Dush(const float deltaTime) {
	if (dush_flag) {
		
	}
}

//void PlayerBase::Attack(const float deltaTime) {
//	switch (burst_state_mode)
//	{
//	case BURST_STATE::NOT_BURST:
//		burst_state_mode = BURST_STATE::FIRST;
//		break;
//	case BURST_STATE::FIRST:
//		SetAnimation(player_model, ACT1);
//		first_burst_start += deltaTime;
//
//		attack_flag = true;
//
//		if (first_burst_start >= 0.15f && DXTK->KeyEvent->pressed.S) {
//			first_burst_flag = true;
//		}
//		if (first_burst_start >= first_burst_end && first_burst_flag) {
//			burst_state_mode = BURST_STATE::SECOND;
//			model->SetTrackPosition(ACT1, 0.0);
//			first_burst_start = 0.0f;
//			first_burst_flag = false;
//		}
//		else if (first_burst_start >= first_burst_end) {
//			burst_state_mode = BURST_STATE::NOT_BURST;
//			model->SetTrackPosition(ACT1, 0.0);
//			first_burst_start = 0.0f;
//			first_burst_flag = false;
//		}
//
//		break;
//	case BURST_STATE::SECOND:
//		SetAnimation(model, ACT2);
//		second_burst_start += deltaTime;
//
//		attack_flag = true;
//
//
//		if (second_burst_start >= 0.15f && DXTK->KeyEvent->pressed.S)
//			second_burst_flag = true;
//
//		if (second_burst_start >= second_burst_end && second_burst_flag) {
//			burst_state_mode = BURST_STATE::THIRD;
//			model->SetTrackPosition(ACT2, 0.0);
//
//			second_burst_start = 0.0f;
//			second_burst_flag = false;
//		}
//		else if (second_burst_start >= second_burst_end) {
//			burst_state_mode = BURST_STATE::NOT_BURST;
//			model->SetTrackPosition(ACT2, 0.0);
//			second_burst_start = 0.0f;
//			second_burst_flag = false;
//		}
//
//		break;
//	case BURST_STATE::THIRD:
//		SetAnimation(model, ACT3);
//		third_burst_start += deltaTime;
//
//		attack_flag = true;
//
//
//		if (third_burst_start >= 0.15f && DXTK->KeyEvent->pressed.S)
//			third_burst_flag = true;
//
//		if (third_burst_start >= third_burst_end) {
//			burst_state_mode = BURST_STATE::NOT_BURST;
//			model->SetTrackPosition(ACT3, 0.0);
//			third_burst_start = 0.0f;
//			third_burst_flag = false;
//		}
//
//		break;
//	}
//
//}


void PlayerBase::Jump(const float deltaTime) {
	if (!jump_flag) {
		jump_flag = true;
		jump_time = 0.0f;
		jump_start_v_ = player_model->Position.y;
	}

	if (jump_flag) {
		jump_time += deltaTime;
		auto pos = player_model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time - half * gravity_ * jump_time * jump_time;
		player_model->SetPosition(pos);
		
		//ジャンプの終了判定
		if (V0 * jump_time < gravity_ * jump_time * jump_time) {
			jump_flag = false;
			auto pl = 0;
		}
	}

}


void PlayerBase::Render() {
	player_model->Draw();
}
void PlayerBase::_2D() {
	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 0.0f),
		DX9::Colors::Red,
		L"座標　%f %f %f",player_pos.x, player_pos.y, player_pos.z
	);
}

//指定されたモーションはTRUE,それ以外はFALSE
void PlayerBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}
