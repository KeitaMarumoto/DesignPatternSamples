#pragma once
#include "../Node/Observer.h"
#include "../Node/ObserverNode.h"
#include "cinder/gl/gl.h"

//オブザーバに通知を送るためにオブジェクトやシーンなどを監視するクラス。
//今回はMainクラスでインスタンスして使っているが、継承させるのもアリ。
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
	void notify(Entity& entity_, Events event_);
};