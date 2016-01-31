#include "Button.h"

namespace GameEngine {
	Button::Button() : _isPushed(false), _sprite(nullptr), _SpriteManager(nullptr), _FontBatcher(nullptr), _InputManager(nullptr) {
	}

	Button::~Button() {
	}

	void Button::onIdle() {
		//Simple default method to set the animation to the idle animation
		_sheet.setAnim(_name + "IDLE");
	}

	void Button::onHover() {
		_sheet.setAnim(_name + "HOVER");
	}

	void Button::onPush() {
		_sheet.setAnim(_name + "PUSH");
	}
}
