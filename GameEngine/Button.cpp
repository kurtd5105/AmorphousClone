#include "Button.h"
#include "FontBatcher.h"
#include "InputManager.h"
#include "Sprite.h"
#include "SpriteManager.h"

namespace GameEngine {
	Button::Button() : _SpriteManager(nullptr), _FontBatcher(nullptr), _InputManager(nullptr), _sprite(nullptr), _isPushed(false) {}

	Button::~Button() {}

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
