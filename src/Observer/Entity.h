#pragma once
#include "cinder/app/MouseEvent.h"
#include "cinder/app/KeyEvent.h"

using namespace ci::app;

class Entity 
{
public:
	Entity() = default;
	Entity(MouseEvent& m_event, KeyEvent& k_event);

	inline const MouseEvent& getMouseEvent() const;
	inline const KeyEvent& getKeyEvent() const;
private:
	MouseEvent mouse_event_;
	KeyEvent key_event_;
};