#include"SoundPlayer.h"

SoundPlayer::SoundPlayer() {
	sound_			= nullptr;
	bgm_instance_	= nullptr;
	timer_			= nullptr;
}

SoundPlayer::~SoundPlayer() {
	delete timer_;
}

void SoundPlayer::Initialize(std::wstring file_name, SOUND_TYPE sound_type) {
	sound_			= XAudio::CreateSoundEffect(DXTK->AudioEngine, file_name.c_str());
	bgm_instance_	= (sound_type == SOUND_TYPE::BGM) ? sound_->CreateInstance() : XAudio::SOUNDEFFECTINSTANCE{};
}

void SoundPlayer::Initialize(std::wstring file_name, SOUND_TYPE sound_type, float playTime) {
	sound_			= XAudio::CreateSoundEffect(DXTK->AudioEngine, file_name.c_str());
	bgm_instance_	= (sound_type == SOUND_TYPE::BGM) ? sound_->CreateInstance() : XAudio::SOUNDEFFECTINSTANCE{};
	timer_			= new OriTimer(playTime, 0.0f);
}

void SoundPlayer::OnRestartSound() {
	if (bgm_instance_)
		Play();
}

void SoundPlayer::Play() const {
	bgm_instance_->Play(true);
}

void SoundPlayer::PlayRoopSE(const float deltaTime) {
	PlayTimeCount(deltaTime);
	if (timer_->TimeOut()) {
		timer_->ResetCountTime();
		PlayOneShot();
	}
}

void SoundPlayer::PlayOneShot() const {
	sound_->Play();
}

void SoundPlayer::PlayTimeCount(const float deltaTime) {
	timer_->Update(deltaTime);
}