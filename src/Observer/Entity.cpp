#include "Entity.h"

Entity::Entity(MouseEvent & m_event, KeyEvent & k_event)
{
	mouse_event_ = m_event;
	key_event_ = k_event;
}

inline const MouseEvent & Entity::getMouseEvent() const
{
	return mouse_event_;
}

inline const KeyEvent & Entity::getKeyEvent() const
{
	return key_event_;
}
