#include "Achievements.h"

void Achievements::onNotify(Entity & entity_, Events event_)
{
	switch (event_) {
	case Events::LEFT_CLICK_FIVE_TIMES:
		entity_.setColor(Color(0, 1, 0));
		break;

	case Events::RIGHT_CLICK_FIVE_TIMES:
		entity_.setColor(Color(1, 0, 1));
		break;

	case Events::PUSH_KEY_X:
		entity_.setColor(Color(1, 0, 0));
		break;

	case Events::PUSH_KEY_Y:
		entity_.setColor(Color(0, 0, 1));
		break;

	case Events::PUSH_KEY_SPACE:
		entity_.setColor(Color(1, 1, 1));
		break;

	default:
		break;
	}
}
