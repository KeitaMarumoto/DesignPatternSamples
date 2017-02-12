#pragma once
#include "../Node/Observer.h"
#include "cinder/gl/gl.h"

//オブザーバによる実績達成的なサンプル。
//今回は描画してあるキューブのカラーを変えるだけ。
class Achievements : public Observer 
{
public:
	void onNotify(Entity& entity_, Events event_);
};