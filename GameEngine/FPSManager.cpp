#include "FPSManager.h"

namespace GameEngine {
	void FPSManager::fpsinit() {
		memset(frametimes, 0, sizeof(frametimes));
		framecount = 0;
		framespersecond = 0;
		frametimelast = SDL_GetTicks();
	}

	void FPSManager::fpsthink() {
		Uint32 frametimesindex;
		Uint32 getticks;
		Uint32 count;
		Uint32 i;

		frametimesindex = framecount % FRAME_VALUES;
		getticks = SDL_GetTicks();
		frametimes[frametimesindex] = getticks - frametimelast;
		frametimelast = getticks;
		framecount++;

		if (framecount < FRAME_VALUES) {
			count = framecount;
		}
		else {
			count = FRAME_VALUES;
		}


		framespersecond = 0;
		for (i = 0; i < count; i++) {
			framespersecond += frametimes[i];
		}

		framespersecond /= count;
		framespersecond = 1000.f / framespersecond;
	}
}
