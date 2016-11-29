#include "Window.h"
#include "Errors.h"
#include <iostream>
#include <GL/glew.h>
#include <SDL/SDL.h>

namespace GameEngine {
	const std::vector<int> Screen::validWidths = {800, 1024, 1280, 1360, 1366, 1440, 1600, 1920};
	const std::vector<int> Screen::validHeights = {600, 768, 720, 768, 768, 900, 900, 1080};

	Window::Window() : _width(0), _height(0), _windowMode(WindowMode::WINDOWED), _window(nullptr), _surface(nullptr) {}

	Window::~Window() {}

	glm::vec2 Window::createWindow(Options* options, std::string name) {
		_height = options->height;
		_width = options->width;
		_windowMode = options->mode;

		//Setup the appropriate flag for the SDL window mode
		auto windowFlag = SDL_WINDOW_OPENGL;
		if(_windowMode == WindowMode::FULLSCREEN) {
			windowFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
		} else if(_windowMode == WindowMode::BORDERLESS) {
			windowFlag = SDL_WINDOW_BORDERLESS;
		}

		//Init SDL and check for init errors
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			fatalSDLError(SDL_GetError(), "SDL Init failed.");
		}

		//Enable double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//Create the SDL window centered using OpenGL
		_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, windowFlag);
		if(_window == nullptr) {
			fatalSDLError(SDL_GetError(), "SDL window creation failed.");
		}

		//Create OpenGL context
		SDL_GLContext glContext = SDL_GL_CreateContext(_window);

		if(glContext == nullptr) {
			fatalSDLError(SDL_GetError(), "Failed to create context.");
		}

		//Initialize glew
		GLenum glError = glewInit();

		if(glError != GLEW_OK) {
			fatalGLError(glError, "Glew initialization failed.");
		}

		//Print the OpenGL version
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		//Set the clear color to rgba of solid black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Turn on alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Turn on VSync
		SDL_GL_SetSwapInterval(1);

		float ratio = (float(_width) / _height);
		glm::vec2 ratioScale = glm::vec2(16.0f, 9.0f);
		if(ratio < 1.7) {
			ratioScale = glm::vec2(4.0f, 3.0f);
		}

		return glm::vec2((float(_width) / BASE_WIDTH), (float(_height) / BASE_HEIGHT));
	}

	void Window::swapBuffer() const {
		SDL_GL_SwapWindow(_window);
	}

	void Window::destroySDLWindow() const {
		SDL_DestroyWindow(_window);
	}
}