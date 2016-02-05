#pragma once

#include "WindowMode.h"

namespace GameEngine {
	struct Options {
		int width, height;
		float music, sfx;
		WindowMode mode;
	};
}