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

	auto pos = player_model->GetPosition();
	

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
		dush_->Update(deltaTime);
	}
}


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
