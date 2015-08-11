#pragma once
#include <GL/glew.h>
#include <string>

namespace GameEngine {
	extern void fatalSDLError(std::string errorSDL, std::string errorNote);
	extern void fatalGLError(GLenum errorGL, std::string errorNote);
}