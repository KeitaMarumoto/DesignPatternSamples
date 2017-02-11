#pragma once
#include "../src/Flyweight/MikuModel.h"
#include "cinder/Rand.h"
#include <memory>

using namespace ci;

// ミクさんの個体の完成形を定義したクラス。
// 描画する数だけインスタンス。
class Miku {
private:
	std::shared_ptr<MikuModel> _model;
	Vec3f _pos;
	float _rot;
	float _speed_value;

public:
	Miku() = default;
	inline Miku(std::shared_ptr<MikuModel>& __model, Vec3f __pos, float __speed)
	{
		_model = __model;
		_pos = __pos;
		_rot = 0.0f;
		_speed_value = 0.5f*__speed;
	}

	//画面奥に向かって移動し、Y軸まわりに回転する。
	inline void move() 
	{
		_rot += _speed_value*5;
		_pos.z += _speed_value;
		if (_pos.z >= 100) {
			_pos.z = -1.0f;
			_rot = 0.0f;
		}
	}

	inline Vec3f getPos() { return _pos; }
	inline float getRot() { return _rot; }
	inline const MikuModel& getMikuModel() const { return *_model; }
};
