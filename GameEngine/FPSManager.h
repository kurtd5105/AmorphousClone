#pragma once
#include <SDL/SDL.h>

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
		Uint32 frametimelast = 0;
		Uint32 framecount = 0;
	};
}