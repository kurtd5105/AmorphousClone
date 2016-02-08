#include "SelectionBox.h"

namespace GameEngine {
	SelectionBox::SelectionBox() {
	}


	SelectionBox::~SelectionBox() {
	}

	void SelectionBox::init(float buttonX, float y, float buttonWidth, float buttonHeight, float textWidth, float depth, std::vector<std::string> options,
							std::string nameLeft, std::string nameRight, std::string textLPath, std::string aniLPath, std::string textRPath, std::string aniRPath,
							Color color, std::function<void(void)> callbackLeft, std::function<void(void)> callbackRight, SpriteManager* manager, FontBatcher* fontBatcher) {
		_leftX = buttonX;
		_rightX = buttonX + buttonWidth + textWidth;
		_textX = buttonX + buttonWidth;
		_y = y;
		_buttonWidth = buttonWidth;
		_textWidth = textWidth;
		_depth = depth;
		_options = options;
		_count = _options.size();
		_index = 0;

		_SpriteManager = manager;
		_FontBatcher = fontBatcher;

		_left.init(_leftX, _y, _buttonWidth, buttonHeight, _depth, textLPath, aniLPath, nameLeft, callbackLeft, _SpriteManager);
		_right.init(_rightX, _y, _buttonWidth, buttonHeight, _depth, textRPath, aniRPath, nameRight, callbackRight, _SpriteManager);

		_color = color;
		_text.init(_options[_index], glm::vec2(_textX, _y), glm::vec2(1, 1), _depth, _color, _FontBatcher);
	}

	void SelectionBox::setSelection(std::string selection) {
		unsigned int index;
		for(index = 0; index < _count; index++) {
			if(_options[index] == selection) {
				setSelection(index);
				return;
			}
		}
	}

	void SelectionBox::setSelection(unsigned int index) {
		_index = index;
		_text.init(_options[_index], glm::vec2(_textX, _y), glm::vec2(1, 1), _depth, _color, _FontBatcher);
	}

	void SelectionBox::setOptions(std::vector<std::string> options) {
		_options = options;
		_count = _options.size();
		_index = 0;
	}

	void SelectionBox::forward() {
		_index++;
		if(_index >= _count) {
			_index = 0;
		}
		_text.init(_options[_index], glm::vec2(_textX, _y), glm::vec2(1, 1), _depth, _color, _FontBatcher);
	}

	void SelectionBox::backward() {
		if(_index == 0) {
			_index = _count - 1;
		} else {
			_index--;
		}
		_text.init(_options[_index], glm::vec2(_textX, _y), glm::vec2(1, 1), _depth, _color, _FontBatcher);
	}
}
