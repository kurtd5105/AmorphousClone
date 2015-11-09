#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <TTF/SDL_ttf.h>
#include <glm/glm.hpp>

#include "Errors.h"
#include "Sprite.h"

namespace GameEngine {
	struct CharGlyph {
	public:
		char character;
		glm::vec4 uvRect;
		glm::vec2 size;
	};

	class Font {
	public:
		Font();
		~Font();

		const int MAX_TEXTURE_RES = 4096;

		void init(std::string path, int point);
	private:
		static std::vector<int>* createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);
		glm::vec2 measure(const char* s);
		int closestPow2(int i);

		CharGlyph* _chars;

		GLuint _id;
		int _fontHeight, _length, _start;
	};
}
