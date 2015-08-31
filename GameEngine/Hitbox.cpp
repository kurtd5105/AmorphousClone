#define _USE_MATH_DEFINES
#include "Hitbox.h"
#include <math.h>

namespace GameEngine {
	Hitbox::Hitbox() {
	}


	Hitbox::~Hitbox() {
	}

	void Hitbox::init(float x, float y, float width, float height, float radius) {
		_info.resize(5);
		_info[0] = x;
		_info[1] = y;
		_info[2] = x + width;
		_info[3] = y + height;
		_info[4] = radius;
		//Set the hitbox type to RECT if the radius is 0. In the future possible hitbox type is passed
		_type = radius == 0 ? HitboxType::RECT : HitboxType::CIRC;
	}

	void Hitbox::translate(float x, float y) {
		_info[0] += x;
		_info[1] += y;
		_info[2] += x;
		_info[3] += y;
	}
}