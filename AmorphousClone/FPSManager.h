#pragma once

#include <SDL/SDL.h>
#include <string.h>

class FPSManager
{
public:

	#define FRAME_VALUES 10
	Uint32 frametimes[FRAME_VALUES];
	Uint32 frametimelast;
	Uint32 framecount;
	float framespersecond;

	void fpsinit();
	void fpsthink();
};

