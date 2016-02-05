#pragma once

#include "Button.h"
#include <math.h>

namespace GameEngine {
	class Slider : public Button {
	public:
		Slider();
		~Slider();

		void init(float x, float y, float width, float height, float lineWidth, float lineHeight, float depth, std::string texPath, std::string aniPath,
				  std::string linePath, Color color, std::function<void(void)> callback, SpriteManager* manager, FontBatcher* fontBatcher, InputManager* inputManager);

		void onIdle() { _isPushed = false; _sheet.setAnim(_name + "IDLE"); }
		void onHover() { _isPushed = false; _sheet.setAnim(_name + "HOVER"); }
		void onPush();

		float getValue() { return _percent; }
	private:
		float _x, _y, _start, _lineWidth, _percent, _max, _width;
		Sprite* _line;
	};
}
