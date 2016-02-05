#include "Slider.h"

namespace GameEngine {
	Slider::Slider() : _line(nullptr), _x(0.0f), _y(0.0f), _start(0.0f), _lineWidth(0.0f), _percent(0.0f), _max(0.0f), _width(0.0f) {
	}


	Slider::~Slider() {
		//delete _text;
	}

	void Slider::init(float x, float y, float width, float height, float lineWidth, float lineHeight, float depth, std::string texPath, std::string aniPath,
					  std::string linePath, Color color, std::function<void(void)> callback, SpriteManager* manager, FontBatcher* fontBatcher, InputManager* inputManager) {
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
		_max = _start + _lineWidth;

		//Note that the line has a higher depth and thus is behind the slider button
		_line = _SpriteManager->addSprite(x + (width/2), y + (height/2) - (lineHeight/2), lineWidth, lineHeight, depth + 1.0f, std::vector<float>{}, linePath);
		_sprite = _SpriteManager->addSprite(x, y, width, height, depth, std::vector<float>{}, texPath);
		_hitbox.init(x, y, width, height, 0);

		_sheet.init(aniPath, _sprite, _SpriteManager->getResourceManager());
		_sheet.setAnim("IDLE");

		//_text = new Text();
		_text.init("0", glm::vec2(x + lineWidth + 10, _y), glm::vec2(1, 1), 1.0f, _color, _FontBatcher);
	}

	void Slider::onPush() {
		//When it is first pushed, set the button to its pushed animation
		if(!_isPushed) {
			_sheet.setAnim(_name + "PUSH");
			_isPushed = true;
		}

		//Get the x position of the mouse
		float x = _InputManager->getMouseCoords()[0];

		//Lock the sprite button to the right end of the slider if the mouse is past the right end of the slider
		if(x > _max) {
			_sprite->translate(_max - _x, 0);
			_hitbox.translate(_max - _x, 0);
			_x = _max;
		//Lock the sprite button to the left end of the slider if the mouse is past the left end of the slider
		} else if(x < _start) {
			_sprite->translate(_start - _x, 0);
			_hitbox.translate(_start - _x, 0);
			_x = _start;
		//Lock the sprite button to the mouse x if the mouse is on the slider
		} else {
			_sprite->translate(x - _x, 0);
			_hitbox.translate(x - _x, 0);
			_x = x;
		}
		
		//Calculate the how far along the button is on the line into a percentage
		_percent = ((_x - _start) / _lineWidth) * 100;
		//Change the text to display that percentage
		_text.init(std::to_string((int)round(_percent)), glm::vec2(_max + 10 + (_width / 2), _y), glm::vec2(1, 1), 1.0f, _color, _FontBatcher);
	}
}
