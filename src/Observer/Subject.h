#pragma once
#include "../src/Observer/Observer.h"
#include "../src/Observer/ObserverNode.h"

//オブザーバに通知を送るためにオブジェクトなどを監視する基底クラス。
class Subject 
{
private:
	ObserverNode* head_;

public:
	Subject()
	: head_(nullptr)
	{}

	void addObserver(ObserverNode* observer_node_, Observer* observer_);
	void removeObserver(ObserverNode* observer_node_);
	void notify(const Entity& entity_, Events event_);
};