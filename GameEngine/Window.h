#pragma once
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <string>

namespace GameEngine {
	enum WindowMode {
		FULLSCREEN, BORDERLESS, WINDOWED
	};

	class Window {
	public:
		Window();
		~Window();

		void createWindow(int width, int height, std::string name, WindowMode windowMode = WindowMode::WINDOWED);
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