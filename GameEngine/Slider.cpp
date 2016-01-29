#include "Slider.h"

namespace GameEngine {
	Slider::Slider() {
	}


	Slider::~Slider() {
	}

	void Slider::init(float x, float y, float width, float height, float lineWidth, float lineHeight, float depth, std::string texPath, std::string aniPath,
					  std::string linePath, Color color, std::function<void(void)> callback, SpriteManager* manager, FontBatcher* fontBatcher, InputManager* inputManager) {
		_name = "";
		_callback = callback;
		_SpriteManager = manager;
		_FontBatcher = fontBatcher;
		_InputManager = inputManager;
		_hitbox.init(x, y, width, height, 0);
		_color = color;
		_x = x;
		_start = x;
		_y = y - 1;
		_width = width;
		_lineWidth = lineWidth;
		_max = _start + _lineWidth;
		_line = _SpriteManager->addSprite(x + (width/2), y + (height/2) - (lineHeight/2), lineWidth, lineHeight, depth, std::vector<float>{}, linePath);
		_sprite = _SpriteManager->addSprite(x, y, width, height, depth, std::vector<float>{}, texPath);
		_sheet.init(aniPath, _sprite, _SpriteManager->getResourceManager());
		_sheet.setAnim("IDLE");
		_text.init("0", glm::vec2(x + lineWidth + 10, _y), glm::vec2(1, 1), 1.0f, _color, _FontBatcher);
	}

	void Slider::onPush() {
		if(!_isPushed) {
			_sheet.setAnim(_name + "PUSH");
			_isPushed = true;
		}
		float x = _InputManager->getMouseCoords()[0];
		if(x > _max) {
			_sprite->translate(_max - _x, 0);
			_hitbox.translate(_max - _x, 0);
			_x = _max;
		} else if(x < _start) {
			_sprite->translate(_start - _x, 0);
			_hitbox.translate(_start - _x, 0);
			_x = _start;
		} else {
			_sprite->translate(x - _x, 0);
			_hitbox.translate(x - _x, 0);
			_x = x;
		}
		
		_percent = ((_x - _start) / _lineWidth) * 100;
		_text.init(std::to_string((int)round(_percent)), glm::vec2(_max + 10 + (_width / 2), _y), glm::vec2(1, 1), 1.0f, _color, _FontBatcher);
	}
}
