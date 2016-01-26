#include "Button.h"

namespace GameEngine {
	Button::Button() {
	}

	Button::~Button() {
	}

	void Button::onHover() {
		_sheet.setAnim(_name + "HOVER");
	}

	void Button::onPush() {
		_sheet.setAnim(_name + "PUSH");
	}
}
