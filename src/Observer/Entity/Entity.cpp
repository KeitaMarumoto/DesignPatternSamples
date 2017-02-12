#include "Entity.h"

Entity::Entity(MouseEvent & m_event, KeyEvent & k_event)
{
	mouse_event_ = m_event;
	key_event_ = k_event;
}

const MouseEvent & Entity::getMouseEvent() const
{
	return mouse_event_;
}

const KeyEvent & Entity::getKeyEvent() const
{
	return key_event_;
}

const Color& Entity::getColor() const
{
	return color_;
}

void Entity::setMouseEvent(MouseEvent & m_event_)
{
	mouse_event_ = m_event_;
}

void Entity::setKeyEvent(KeyEvent & k_event_)
{
	key_event_ = k_event_;
}

void Entity::setColor(Color& col_)
{
	color_ = col_;
}
