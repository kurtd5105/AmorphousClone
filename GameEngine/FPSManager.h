#pragma once

#include <SDL/SDL.h>
#include <string.h>

namespace GameEngine {
	class FPSManager
	{
	public:
		static const int FRAME_VALUES = 30;
		float framespersecond;

		void fpsinit();
		void fpsthink();
		Uint32 getFrameTime();

	private:
		Uint32 frametimes[FRAME_VALUES];
		Uint32 frametimelast;
		Uint32 framecount;
	};
}