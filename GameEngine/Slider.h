#pragma once

#include "Button.h"

namespace GameEngine {
	class Slider : public Button {
	public:
		Slider();
		~Slider();

		void init(float x, float y, float width, float height, float lineWidth, float lineHeight, float depth, float value, std::string texPath, std::string aniPath,
				  std::string linePath, Color color, std::function<void(void)> callback, SpriteManager* manager, FontBatcher* fontBatcher, InputManager* inputManager,
				  std::pair<int, int> minMax = std::pair<int, int>(0, 100));

		void onIdle() override { _isPushed = false; _sheet.setAnim(_name + "IDLE"); }
		void onHover() override { _isPushed = false; _sheet.setAnim(_name + "HOVER"); }
		void onPush() override;

		float getValue() const { return _value; }
		float getPercent() const { return _percent; }
		void setPercent(float percent);
		void setValue(float value);
	private:
		void setPosition();

		int _min, _max;
		float _x, _y, _start, _lineWidth, _percent, _value, _maxX, _width, _clickX;

		Sprite* _line;
	};
}
