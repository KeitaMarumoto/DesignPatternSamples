#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"
#include "../Node/Observer.h"

//通知を受信すると音楽を鳴らす。
class FanfareSound : public Observer 
{
private:
	audio::FilePlayerNodeRef file_player_;
	audio::GainNodeRef gain_;
	audio::SourceFileRef source_x_;
	audio::SourceFileRef source_y_;
	audio::SourceFileRef source_left_click_;
	audio::SourceFileRef source_right_click_;

public:
	FanfareSound();
	void onNotify(Entity& entity_, Events event_);
	void setupAudio();
	void startFanfare(const audio::SourceFileRef& source_, float fanfare_gain_);
};