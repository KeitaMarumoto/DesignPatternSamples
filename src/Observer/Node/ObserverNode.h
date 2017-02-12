#pragma once
#include "../Node/Observer.h"
#include "../Subject/Subject.h"

//オブザーバを格納しているノード。連結リスト構造。
//オブザーバ本体を連結リストにすると一つのサブジェクトにしか登録できなくなるため
//ノードをリストにしてオブザーバのポインタを持たせている。
class ObserverNode 
{
	friend class Subject;
	friend class Observer;
private:
	ObserverNode* next_;
	Observer* observer_;

public:
	ObserverNode()
	: next_(nullptr),
	  observer_(nullptr)
	{}
};