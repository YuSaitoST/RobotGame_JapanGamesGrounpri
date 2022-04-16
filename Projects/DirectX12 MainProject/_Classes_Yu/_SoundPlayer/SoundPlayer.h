#pragma once

#include"Base/pch.h"
#include"Base/dxtk.h"
#include"_Classes_Yu/_UI/_OriTimer/OriTimer.h"

using namespace DirectX;

enum SOUND_TYPE { BGM, SE };

class SoundPlayer {
public:
	SoundPlayer();
	virtual ~SoundPlayer();

	void Initialize(std::wstring file_name, SOUND_TYPE sound_type);
	void Initialize(std::wstring file_name, SOUND_TYPE sound_type, float playTime);
	void OnRestartSound();

	void Play() const;
	void PlayOneShot() const;
	void PlayRoopSE(const float deltaTime);
	
	void PlayTimeCount(const float deltaTime);

	bool isFined() const { return timer_->TimeOut(); };

private:
	XAudio::SOUNDEFFECT sound_;
	XAudio::SOUNDEFFECTINSTANCE bgm_instance_;

	OriTimer* timer_;
};