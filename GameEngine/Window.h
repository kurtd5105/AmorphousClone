#pragma once
#include <SDL/SDL.h>
#include <string>
#include <vector>

#include "Options.h"
#include "WindowMode.h"
#include <glm/detail/type_vec2.hpp>

namespace GameEngine {
	struct Screen {
		static const std::vector<int> validWidths;
		static const std::vector<int> validHeights;
	};

	class Window {
	public:
		Window();
		~Window();

		static const int BASE_WIDTH = 1280;
		static const int BASE_HEIGHT = 720;

		glm::vec2 createWindow(Options* options, std::string name);
		void swapBuffer() const;
		void destroySDLWindow() const;

		int getScreenWidth() const { return _width; }
		int getScreenHeight() const { return _height; }
		WindowMode getWindowMode() const { return _windowMode; }

		

	private:
		int _width, _height;

		WindowMode _windowMode;

		SDL_Window* _window;
		SDL_Surface* _surface;
	};
}
