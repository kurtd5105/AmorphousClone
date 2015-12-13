#pragma once
#include "Hitbox.h"

namespace GameEngine {
	namespace Collision {
		extern bool checkCollide(Hitbox a, Hitbox b);
		extern bool checkClick(Hitbox a, float x, float y);
	};
}
