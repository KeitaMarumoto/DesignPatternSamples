#pragma once

#include "../Events.h"
#include "../Entity/Entity.h"
#include "../Subject/Subject.h"

//オブザーバ本体。
//何かSubjectから通知が送られたときに受け取るための基底クラス。
//これを継承したクラスはすべてオブザーバとなる。
class Observer 
{
	friend class Subject;
public:
	Observer()
	{}
	
	virtual ~Observer() {}
	virtual void onNotify(Entity& entity_, Events event_) = 0;
};