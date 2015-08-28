#pragma once

#include <SDL/SDL.h>
#include <string.h>

namespace GameEngine {
	class FPSManager
	{
	public:

		float framespersecond;

		void fpsinit();
		void fpsthink();

	private:

		#define FRAME_VALUES 10
		Uint32 frametimes[FRAME_VALUES];
		Uint32 frametimelast;
		Uint32 framecount;
	};
}