#pragma once
#include <GL/glew.h>

struct GLTexture {
	GLuint id;
	int width, height;
};

struct GLRawTexture {
	std::vector<unsigned char> data;
	int width, height;
};