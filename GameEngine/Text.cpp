#include "Text.h"

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
	Text::Text() : _index(0) {
	}


	Text::~Text() {
	}

	void Text::init(std::string text, glm::vec2 position, glm::vec2 scaling, float depth, Color tint, FontBatcher& batcher) {
		glm::vec2 tp = position;

		Font* font = batcher.getFont();

		int fontHeight = font->getFontHeight();
		int start = font->getFontHeight();
		int length = font->getFontLength();

		CharGlyph* glyphs = font->getFontGlyphs();

		for(int i = 0; text[i] != 0; i++) {
			char c = text[i];
			if(text[i] == '\n') {
				tp.y += fontHeight * scaling.y;
				tp.x = position.x;
			} else {
				// Check for correct glyph
				int gi = c - start;
				if(gi < 0 || gi >= length)
					gi = length;
				glm::vec4 destRect(tp, glyphs[gi].size * scaling);
				_index = batcher.add(destRect, glyphs[gi].uvRect, depth, tint);
				tp.x += glyphs[gi].size.x * scaling.x;
			}
		}
	}
}