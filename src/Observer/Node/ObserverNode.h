#pragma once
#include "../Node/Observer.h"
#include "../Subject/Subject.h"
#include <memory>

//オブザーバを格納しているノード。連結リスト構造。
//オブザーバ本体を連結リストにすると一つのサブジェクトにしか登録できなくなるため
//ノードをリストにしてオブザーバのポインタを持たせている。
class ObserverNode 
{
	friend class Subject;
	friend class Observer;
private:
	ObserverNode* next_;
	std::shared_ptr<Observer> observer_;

public:
	ObserverNode()
	: next_(nullptr),
	  observer_(nullptr)
	{}

	ObserverNode(std::shared_ptr<Observer> obs_) 
	{
		observer_ = obs_;
	}
};