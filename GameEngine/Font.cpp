#include "Font.h"
//Adapted from Benjamin Arnold's SpriteFont
/*
This is a modified version of the SpriteFont class from the
Seed Of Andromeda source code.
Use it for any of your projects, commercial or otherwise,
free of charge, but do not remove this disclaimer.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.

November 28 2014
Original Author: Cristian Zaloj
Modified By: Benjamin Arnold, kurtd5105
*/
namespace GameEngine {
	//95 characters (32-126 ASCII char range)
	Font::Font() : _id(0), _length(95), _start(32) {
	}


	Font::~Font() {
	}

	void Font::operator=(Font& font) {
		_fontHeight = font.getFontHeight();
		_start = font.getFontStart();
		_length = font.getFontLength();

		_chars = font.getFontGlyphs();
		_id = font.getFontID();
	}

	void Font::init(std::string path, int point) {
		// Initialize SDL_ttf
		if(!TTF_WasInit()) {
			TTF_Init();
		}
		//Create a TTF font using the path and with the specified font point
		TTF_Font* f = TTF_OpenFont(path.c_str(), point);
		if(f == nullptr) {
			fatalGenericError("Failed to open TTF font" + path);
		}
		_fontHeight = TTF_FontHeight(f);
		int padding = point/8;

		// First neasure all the regions
		glm::ivec4* charRects = new glm::ivec4[_length];
		int advance;
		for(int i = 0; i < _length; i++) {
			TTF_GlyphMetrics(f, (char)(i + _start), &charRects[i].x, &charRects[i].z, &charRects[i].y, &charRects[i].w, &advance);
			charRects[i].z -= charRects[i].x;
			charRects[i].x = 0;
			charRects[i].w -= charRects[i].y;
			charRects[i].y = 0;
		}

		// Find best partitioning of chars
		int rows = 1, w, h, bestWidth = 0, bestHeight = 0, area = MAX_TEXTURE_RES * MAX_TEXTURE_RES, bestRows = 0;
		std::vector<int>* bestPartition = nullptr;
		while(rows <= _length) {
			h = rows * (padding + _fontHeight) + padding;
			auto generatedRows = createRows(charRects, _length, rows, padding, w);

			// Desire a power of 2 texture
			w = closestPow2(w);
			h = closestPow2(h);

			// A texture must be feasible
			if(w > MAX_TEXTURE_RES || h > MAX_TEXTURE_RES) {
				rows++;
				delete[] generatedRows;
				continue;
			}

			// Check for minimal area
			if(area >= w * h) {
				if(bestPartition) delete[] bestPartition;
				bestPartition = generatedRows;
				bestWidth = w;
				bestHeight = h;
				bestRows = rows;
				area = bestWidth * bestHeight;
				rows++;
			} else {
				delete[] generatedRows;
				break;
			}
		}

		// Can a bitmap font be made?
		if(!bestPartition) {
			fatalGenericError("Failed to Map TTF font %s to texture: " + path);
		}
		// Create the texture
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bestWidth, bestHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		// Now draw all the chars
		SDL_Color fg = {255, 255, 255, 255};
		int ly = padding;
		for(int ri = 0; ri < bestRows; ri++) {
			int lx = padding;
			for(int ci = 0; ci < bestPartition[ri].size(); ci++) {
				int gi = bestPartition[ri][ci];

				SDL_Surface* charSurface = TTF_RenderGlyph_Blended(f, (char)(_start + gi), fg);

				// Pre-multiplication occurs here
				unsigned char* sp = (unsigned char*)charSurface->pixels;
				int cp = charSurface->w * charSurface->h * 4;
				for(int i = 0; i < cp; i += 4) {
					float a = sp[i + 3] / 255.0f;
					sp[i] *= a;
					sp[i + 1] = sp[i];
					sp[i + 2] = sp[i];
				}

				// Save char image and update coordinates
				glTexSubImage2D(GL_TEXTURE_2D, 0, lx, bestHeight - ly - 1 - charSurface->h, charSurface->w, charSurface->h, GL_BGRA, GL_UNSIGNED_BYTE, charSurface->pixels);
				charRects[gi].x = lx;
				charRects[gi].y = ly;
				charRects[gi].z = charSurface->w;
				charRects[gi].w = charSurface->h;

				SDL_FreeSurface(charSurface);
				charSurface = nullptr;

				lx += charRects[gi].z + padding;
			}
			ly += _fontHeight + padding;
		}

		// Draw the unsupported char
		int rs = padding - 1;
		int* pureWhiteSquare = new int[rs * rs];
		memset(pureWhiteSquare, 0xffffffff, rs * rs * sizeof(int));
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rs, rs, GL_RGBA, GL_UNSIGNED_BYTE, pureWhiteSquare);
		delete[] pureWhiteSquare;
		pureWhiteSquare = nullptr;

		// Set some texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Create spriteBatch chars
		_chars = new CharGlyph[_length + 1];
		for(int i = 0; i < _length; i++) {
			_chars[i].character = (char)(_start + i);
			_chars[i].size = glm::vec2(charRects[i].z, charRects[i].w);
			_chars[i].uvRect = glm::vec4(
				(float)charRects[i].x / (float)bestWidth,
				(float)charRects[i].y / (float)bestHeight,
				(float)charRects[i].z / (float)bestWidth,
				(float)charRects[i].w / (float)bestHeight
				);
		}
		_chars[_length].character = ' ';
		_chars[_length].size = _chars[0].size;
		_chars[_length].uvRect = glm::vec4(0, 0, (float)rs / (float)bestWidth, (float)rs / (float)bestHeight);

		glBindTexture(GL_TEXTURE_2D, 0);
		delete[] charRects;
		delete[] bestPartition;
		TTF_CloseFont(f);
	}

	std::vector<int>* Font::createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w) {
		// Blank initialize
		std::vector<int>* l = new std::vector<int>[r]();
		int* cw = new int[r]();
		for(int i = 0; i < r; i++) {
			cw[i] = padding;
		}

		// Loop through all glyphs
		for(int i = 0; i < rectsLength; i++) {
			// Find row for placement
			int ri = 0;
			for(int rii = 1; rii < r; rii++) {
				if(cw[rii] < cw[ri]) {
					ri = rii;
				}
			}	 

			// Add width to that row
			cw[ri] += rects[i].z + padding;

			// Add glyph to the row list
			l[ri].push_back(i);
		}

		// Find the max width
		w = 0;
		for(int i = 0; i < r; i++) {
			if(cw[i] > w) w = cw[i];
		}

		return l;
	}

	glm::vec2 Font::measure(const char* s) {
		glm::vec2 size(0, _fontHeight);
		float cw = 0;
		for(int si = 0; s[si] != 0; si++) {
			char c = s[si];
			if(s[si] == '\n') {
				size.y += _fontHeight;
				if(size.x < cw)
					size.x = cw;
				cw = 0;
			} else {
				// Check for correct glyph
				int gi = c - _start;
				if(gi < 0 || gi >= _length)
					gi = _length;
				cw += _chars[gi].size.x;
			}
		}
		if(size.x < cw)
			size.x = cw;
		return size;
	}

	int Font::closestPow2(int i) {
		i--;
		int pi = 1;
		while(i > 0) {
			i >>= 1;
			pi <<= 1;
		}
		return pi;
	}
}