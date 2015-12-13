#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <TTF/SDL_ttf.h>

#include "Errors.h"

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

		int getFontHeight() { return _fontHeight; }
		int getFontStart() { return _start; }
		int getFontLength() { return _length; }

		CharGlyph* getFontGlyphs() { return _chars; }
		GLuint getFontID() { return _id; }
	private:
		static std::vector<int>* createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);
		glm::vec2 measure(const char* s);
		int closestPow2(int i);

		CharGlyph* _chars;

		GLuint _id;
		int _fontHeight, _length, _start;
	};
}
