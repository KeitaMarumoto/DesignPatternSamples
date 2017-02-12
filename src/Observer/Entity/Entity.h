#pragma once
#include "cinder/app/MouseEvent.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/gl/gl.h"

using namespace ci::app;
using namespace ci;

//色々なパラメータを持っておく汎用データクラス。
class Entity 
{
public:
	Entity() = default;
	Entity(MouseEvent& m_event, KeyEvent& k_event);

	const MouseEvent& getMouseEvent() const;
	const KeyEvent& getKeyEvent() const;
	const Color& getColor() const;
	void setMouseEvent(MouseEvent& m_event_);
	void setKeyEvent(KeyEvent& k_event_);
	void setColor(Color& col_);
private:
	MouseEvent mouse_event_;
	KeyEvent key_event_;
	Color color_;
};