#pragma once

#include "../src/Observer/Events.h"
#include "../src/Observer/Entity.h"

class Observer 
{
public:
	virtual ~Observer() {}
	virtual void onNotify(Entity& entity_, Events event_) = 0;
};