#pragma once
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <string>

#include "Options.h"
#include "WindowMode.h"

namespace GameEngine {
	class Window {
	public:
		Window();
		~Window();

		void createWindow(Options* options, std::string name);
		void swapBuffer();
		void destroySDLWindow();

		int getScreenWidth() { return _width; }
		int getScreenHeight() { return _height; }
		WindowMode getWindowMode() { return _windowMode; }

	private:
		int _width, _height;

		WindowMode _windowMode;

		SDL_Window* _window;
		SDL_Surface* _surface;
	};
}