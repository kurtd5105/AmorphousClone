#include "Button.h"

namespace GameEngine {
	Button::Button() {
	}

	Button::~Button() {
	}

	void Button::onIdle() {
		_sheet.setAnim(_name + "IDLE");
	}

	void Button::onHover() {
		_sheet.setAnim(_name + "HOVER");
	}

	void Button::onPush() {
		_sheet.setAnim(_name + "PUSH");
	}
}
