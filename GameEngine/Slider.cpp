#include "Slider.h"
#include <math.h>

namespace GameEngine {
	Slider::Slider() : _min(0), _max(0), _x(0.0f), _y(0.0f), _start(0.0f), _lineWidth(0.0f), _percent(0.0f), _value(0), _maxX(0.0f), _width(0.0f), _clickX(0), _line(nullptr){}

	Slider::~Slider() {
		//delete _text;
	}

	void Slider::init(float x, float y, float width, float height, float lineWidth, float lineHeight, float depth, float value, std::string texPath, std::string aniPath,
					  std::string linePath, Color color, std::function<void(void)> callback, SpriteManager* manager, FontBatcher* fontBatcher, InputManager* inputManager,
					  std::pair<int, int> minMax) {
		_name = "";
		_callback = callback;
		_SpriteManager = manager;
		_FontBatcher = fontBatcher;
		_InputManager = inputManager;

		_color = color;
		_x = x;
		_start = x;
		_y = y - 1;
		_width = width;
		_lineWidth = lineWidth;
		_maxX = _start + _lineWidth;

		_min = minMax.first;
		_max = minMax.second;

		//Note that the line has a higher depth and thus is behind the slider button
		_line = _SpriteManager->addSprite(x + (width/2), y + (height/2) - (lineHeight/2), lineWidth, lineHeight, depth + 1.0f, std::vector<float>{}, linePath);
		_sprite = _SpriteManager->addSprite(x, y, width, height, depth, std::vector<float>{}, texPath);
		_hitbox.init(x, y, width, height, 0, RECT);

		_sheet.init(aniPath, _sprite, _SpriteManager->getResourceManager());
		_sheet.setAnim("IDLE");

		setValue(value);
	}

	void Slider::setPercent(float percent) {
		if(percent > 100.0f) {
			percent = 100.0f;
		} else if(percent < 0.0f) {
			percent = 0.0f;
		}
		_percent = percent;
		_value = (_max * (_percent / 100)) + (_min * (1 - (_percent / 100)));
		_text.init(std::to_string(int(round(_value))), glm::vec2(_maxX + 10 + (_width / 2), _y), glm::vec2(1, 1), 1.0f, _color, _FontBatcher);
		setPosition();
	}

	void Slider::setValue(float value) {
		if(value > _max) {
			value = 100.0f;
		} else if(value < _min) {
			value = 0.0f;
		}
		_value = value;
		_percent = (_value / (_max - _min)) * 100;
		_text.init(std::to_string(int(round(_value))), glm::vec2(_maxX + 10 + (_width / 2), _y), glm::vec2(1, 1), 1.0f, _color, _FontBatcher);
		setPosition();
	}

	void Slider::setPosition() {
		auto offset = (_lineWidth * (_percent / 100));
		if(_x + offset > _maxX) {
			offset = _maxX - _x;
		} else if(_x + offset < _start || int(round(_value)) == _min) {
			offset = _start - _x;
		}
		_sprite->translate(offset, 0);
		_hitbox.translate(offset, 0);
		_x += offset;
	}

	void Slider::onPush() {
		//Get the x position of the mouse
		auto x = _InputManager->getMouseCoords()[0];
		
		//When it is first pushed, set the button to its pushed animation
		if(!_isPushed) {
			_sheet.setAnim(_name + "PUSH");
			_clickX = x - _x;
			_isPushed = true;
		}

		float clickOffset = x - _clickX;
		//Lock the sprite button to the right end of the slider if the mouse is past the right end of the slider
		if(clickOffset > _maxX) {
			_sprite->translate(_maxX - _x, 0);
			_hitbox.translate(_maxX - _x, 0);
			_x = _maxX;
		//Lock the sprite button to the left end of the slider if the mouse is past the left end of the slider
		} else if(clickOffset < _start) {
			_sprite->translate(_start - _x, 0);
			_hitbox.translate(_start - _x, 0);
			_x = _start;
		//Lock the sprite button to the mouse x if the mouse is on the slider
		} else {
			_sprite->translate(clickOffset - _x, 0);
			_hitbox.translate(clickOffset - _x, 0);
			_x = clickOffset;
		}
		
		//Calculate the how far along the button is on the line into a percentage
		_percent = ((_x - _start) / _lineWidth) * 100;
		_value = (_max * (_percent / 100)) + (_min * (1 - (_percent / 100)));
		//Change the text to display that percentage
		_text.init(std::to_string(int(round(_value))), glm::vec2(_maxX + 10 + (_width / 2), _y), glm::vec2(1, 1), 1.0f, _color, _FontBatcher);
	}
}
