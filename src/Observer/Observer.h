#pragma once

#include "../src/Observer/Events.h"
#include "../src/Observer/Entity.h"
#include "../src/Observer/Subject.h"

//オブザーバ本体。
//何かSubjectから通知が送られたときに受け取るための基底クラス。これを継承したクラスはすべてオブザーバとなる。
class Observer 
{
	friend class Subject;
public:
	Observer()
	{}
	
	virtual ~Observer() {}
	virtual void onNotify(const Entity& entity_, Events event_) = 0;
};