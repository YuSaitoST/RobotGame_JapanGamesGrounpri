#include "PlayerBase.h"

#include<stdio.h>
#include<cstdlib>

#include "_Classes_Yu/_FIelds/ConstiateParam.h"
#include "_Classes_Yu/_PlayerInformation/PlayerInformation.h"
#include "_Classes_Yu/_InputClasses/UseKeyCheck.h"


PlayerBase::PlayerBase() {
	cp_ = nullptr;
	SetBaseMember(OBJ_TYPE::PLAYER, SimpleMath::Vector3::Zero, 1.0f);

	player_model = nullptr;
	pos_ = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	speed = 0.0f;

	//ダッシュ 関数
	Boost_zero = 0;//オーバーヒートの初期値
	Boost_max  = 0; //オーバーヒートの最大値
	overheart_flag = false; //オーバーヒートのフラグ


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

	pos_ = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	speed = 60.0f;

	//ダッシュ 関数
	Boost_zero = 0;     //オーバーヒートの初期値
	Boost_max  = 100;   //オーバーヒートの最大値
	overheart_flag = false; //オーバーヒートのフラグ


	//ジャンプ 関数
	jump_flag = false;
	jump_time = 0.0f;
	jump_start_v_ = 0.0f;
	//1/2
	half = 0.5f;
	//重力加速度
	gravity_ = 50.0f;
	//初速
	V0 = 40.0f;

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
	player_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player\\SwordManEX\\armor_red2_0210b.X");
	player_model->SetScale(0.1f);
	
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	debag_font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	time_font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}
void PlayerBase::LoadEffect() {

}

void LoadCsv() {
	FILE* file;  // csv入れる変数
 /*
	_wfopen_sでファイルを開く、L"r"は開き方の指定(今回は読み込み)
	変数に代入するのは、読み込めたかのチェックのため
 */

	auto a = _wfopen_s(&file, L"PlayerParams.csv", L"r");
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

void PlayerBase::Setting(const float deltaTime) {
	player_model->SetRotation(0.0f, XMConvertToRadians(180.0f), 0.0f);
	pos_ = player_model->GetPosition();
	
	//移動制限
	pos_ = SimpleMath::Vector3(
		pos_.x = std::min(std::max(0.0f, pos_.x), FLParams.LENGHT_OF_A_SIDE),
		pos_.y = std::min(std::max(0.0f, pos_.y), 10000.0f),
		pos_.z = std::min(std::max(0.0f, pos_.z), FLParams.LENGHT_OF_A_SIDE)
	);

	player_model->AdvanceTime(deltaTime);
	player_model->SetPosition(pos_);
}

void PlayerBase::Update(const float deltaTime) {
	SetAnimation(player_model, STAND);

	
	UpdateToMorton();
}

void PlayerBase::Move(const float deltaTime) {
	forward_ = Vector3(-Press.DirectionKey().x, 0.0f, Press.DirectionKey().y);
	Vector3 amountMove = forward_ * speed * deltaTime;
	player_model->Move(amountMove);
	
	if (Press.MovePlayerStateUp() || Press.MovePlayerStateDown() || Press.MovePlayerStateLeft() || Press.MovePlayerStateRight()) {
		SetAnimation(player_model, RUN);
	}
}


void PlayerBase::Dush(const float deltaTime) {
	if (!overheart_flag) {
		//ダッシュを押している間だけスピードUP
		if (Press.DushStateKey()) {
			speed = 120.0f;	
			Boost_max -= 1 * deltaTime;
		}
		else {
			//離したらブーストゲージ回復
			speed = 60.0f;
			Boost_max += 2;
		}

		if (Boost_max == Boost_zero) {
			speed = 60.0f;
			overheart_flag = true;
		}
	}

	//オーバーヒート中
	if (overheart_flag)
		overheart_time += deltaTime;
	if (overheart_time >= overheart_max) {
		overheart_flag = false;
		overheart_time = 0.0f;
	}


	Boost_max = std::clamp(Boost_max, 0, 100);
}

//近接攻撃
void PlayerBase::Attack(const float deltaTime) {
	attackState_ = AttackState::Adjacent;
	switch (burst_state_mode)
	{
	case BURST_STATE::NOT_BURST:
		if (Press.AtackEventKey())
			burst_state_mode = BURST_STATE::FIRST;
		break;
	case BURST_STATE::FIRST:
		
		frist_reception_time += deltaTime;

		//受付時間内に攻撃ボタンを押したらフラグが立ち次の攻撃に移る
		if (frist_reception_time <= frist_reception_max && 
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
		}

		break;
	case BURST_STATE::THIRD:
		
		third_reception_time += deltaTime;
		//終わり
		if (third_reception_time >= third_reception_max) {
			third_reception_time = 0.0f;
			third_reception_time = false;
			burst_state_mode = BURST_STATE::NOT_BURST;

		}
		break;
	}

}

void PlayerBase::Shot(const float deltaTime) {
	attackState_ = AttackState::Shooting;
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
			jump_flag = false;
		}
	}

}

void PlayerBase::Render() {
	player_model->Draw();
}

void PlayerBase::Render(DX9::SKINNEDMODEL& model) {
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
			DX9::Colors::Blue,
			L"0"
		);
	}
	else if (burst_state_mode == BURST_STATE::FIRST) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Blue,
			L"1"
		);

		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Blue,
			L"受付時間 %f", frist_reception_time
		);
	}
	else if (burst_state_mode == BURST_STATE::SECOND) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Blue,
			L"2"
		);

		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Blue,
			L"受付時間 %f", second_reception_time
		);

	}
	else if (burst_state_mode == BURST_STATE::THIRD) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 30.0f),
			DX9::Colors::Blue,
			L"3"
		);


		DX9::SpriteBatch->DrawString(
			time_font.Get(),
			SimpleMath::Vector2(0.0f, 60.0f),
			DX9::Colors::Blue,
			L"受付時間 %f", third_reception_time
		);

	}

	DX9::SpriteBatch->DrawString(
		debag_font.Get(),
		SimpleMath::Vector2(0.0f, 100.0f),
		DX9::Colors::Green,
		L"ブーストゲージ %d", Boost_max
	);

	if (overheart_flag) {
		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 130.0f),
			DX9::Colors::Blue,
			L"オーバーヒート ON"
		);

		DX9::SpriteBatch->DrawString(
			debag_font.Get(),
			SimpleMath::Vector2(0.0f, 160.0f),
			DX9::Colors::Blue,
			L"オーバーヒート解除まで残り %f 秒",(int)overheart_time
		);

	}
}


//指定されたモーションはTRUE,それ以外はFALSE
void PlayerBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}
