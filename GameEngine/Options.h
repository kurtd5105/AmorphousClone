#pragma once

#include "WindowMode.h"

namespace GameEngine {
	struct Options {
		int width, height;
		unsigned int spawnCount, spawnRate;
		float music, sfx;
		WindowMode mode;
	};
}