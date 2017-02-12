#include "FanfareSound.h"

FanfareSound::FanfareSound()
{
	setupAudio();
}

void FanfareSound::onNotify(Entity & entity_, Events event_)
{
	switch (event_) {
	case Events::LEFT_CLICK_FIVE_TIMES:
		startFanfare(source_left_click_, 0.85f);
		break;

	case Events::RIGHT_CLICK_FIVE_TIMES:
		startFanfare(source_right_click_, 0.7f);
		break;

	case Events::PUSH_KEY_X:
		startFanfare(source_x_, 0.4f);
		break;

	case Events::PUSH_KEY_Y:
		startFanfare(source_y_, 0.6f);
		break;

	case Events::PUSH_KEY_SPACE:
		if (file_player_->isEnabled()) {
			file_player_->stop();
		}
		break;

	default:
		break;
	}
}

void FanfareSound::setupAudio()
{
	source_x_ = audio::load(ci::app::loadAsset("Observer/fight.wav"));
	source_y_ = audio::load(ci::app::loadAsset("Observer/trans-am_raiser.mp3"));
	source_left_click_= audio::load(ci::app::loadAsset("Observer/gundam00_op1.mp3"));
	source_right_click_ = audio::load(ci::app::loadAsset("Observer/gundam00_op2.mp3"));

	audio::Context* ctx = audio::master();
	ctx->enable();

	file_player_ = ctx->makeNode(new audio::FilePlayerNode());
	file_player_->setSourceFile(source_x_);
	gain_ = ctx->makeNode(new audio::GainNode());
	gain_->setValue(0.5f);

	file_player_ >> gain_ >> ctx->getOutput();
}

void FanfareSound::startFanfare(const audio::SourceFileRef& source_, float fanfare_gain_)
{
	file_player_->setSourceFile(source_);
	gain_->setValue(fanfare_gain_);
	file_player_->start();
}