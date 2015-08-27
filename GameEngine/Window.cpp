#include "Window.h"
#include <iostream>
#include "Errors.h"

namespace GameEngine {
	//using namespace GameEngine;
	Window::Window() :
		_width(0),
		_height(0),
		_window(nullptr),
		_surface(nullptr) {
	}


	Window::~Window() {
	}

	void Window::createWindow(int width, int height, std::string name, WindowMode windowMode) {
		_height = height;
		_width = width;
		_windowMode = windowMode;

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

		//Turn on VSync
		//SDL_GL_SetSwapInterval(1);
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(_window);
	}

	void Window::destroySDLWindow() {
		SDL_DestroyWindow(_window);
	}
}