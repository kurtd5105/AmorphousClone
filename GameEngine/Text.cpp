#include "Text.h"
#include "Font.h"
//#include <iostream>
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
	Text::Text() : _used(false), _index(0), _length(0), _text(""), _position(0.0f, 0.0f), _scaling(0.0f, 0.0f), _depth(1.0f), _batcher(nullptr) {
		Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;
		_tint = color;
	}


	Text::~Text() {
		if(_used) {
			clear();
			_batcher->updateBatch();
		}
	}

	void Text::init(std::string text, glm::vec2 position, glm::vec2 scaling, float depth, Color tint, FontBatcher* batcher) {
		_text = text;
		_position = position;
		_scaling = scaling;
		_depth = depth;
		_tint = tint;
		_batcher = batcher;
		if(_used) {
			clear();
		}// else {
		//	_batcher->addRef();
		//}
		_length = _text.length();
		display();
		_used = true;
		_batcher->updateBatch();
	}

	void Text::clear() const {
		_batcher->remove(_index);
		//_batcher->remove(this);
	}

	void Text::changeText(std::string text) {
		clear();
		_text = text;
		_length = _text.length();
		display();
		_used = true;
		_batcher->updateBatch();
	}

	void Text::display() {
		auto tp = _position;

		auto font = _batcher->getFont();

		auto fontHeight = font->getFontHeight();
		auto start = font->getFontStart();
		auto length = font->getFontLength();

		auto glyphs = font->getFontGlyphs();
		if(!_used) {
			_index = _batcher->addString();
		}

		for(int i = 0; _text[i] != 0; i++) {
			char c = _text[i];
			if(_text[i] == '\n') {
				tp.y += fontHeight * _scaling.y;
				tp.x = _position.x;
			} else {
				// Check for correct glyph
				auto gi = c - start;
				if(gi < 0 || gi >= length)
					gi = length;
				glm::vec4 destRect(tp, glyphs[gi].size * _scaling);
				//Add the character to the font batcher
				_batcher->add(destRect, glyphs[gi].uvRect, _depth, _tint, _index);
				tp.x += glyphs[gi].size.x * _scaling.x;
			}
		}
	}
}