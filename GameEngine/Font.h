#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

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

		void operator=(Font& font);
		void init(std::string path, int point);

		int getFontHeight() const { return _fontHeight; }
		int getFontStart() const { return _start; }
		int getFontLength() const { return _length; }

		CharGlyph* getFontGlyphs() const { return _chars; }
		GLuint getFontID() const { return _id; }
		
		glm::vec2 measure(const char* s) const;
	private:
		static std::vector<int>* createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);
		
		static int closestPow2(int i);

		CharGlyph* _chars;

		GLuint _id;
		int _fontHeight, _length, _start;
	};
}
