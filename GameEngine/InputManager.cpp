#include "InputManager.h"

namespace GameEngine {
	InputManager::InputManager() : _keys(nullptr), _LMB(false), _mouseX(0), _mouseY(0) {}


	InputManager::~InputManager() {}

	void InputManager::update() {
		_keyPresses.resize(6);
		_keys = SDL_GetKeyboardState(nullptr);
		_keyPresses[0] = _keys[SDL_SCANCODE_W] > 0 ? true : false;
		_keyPresses[1] = _keys[SDL_SCANCODE_A] > 0 ? true : false;
		_keyPresses[2] = _keys[SDL_SCANCODE_S] > 0 ? true : false;
		_keyPresses[3] = _keys[SDL_SCANCODE_D] > 0 ? true : false;
		_keyPresses[4] = _keys[SDL_SCANCODE_Q] > 0 ? true : false;
		_keyPresses[5] = _keys[SDL_SCANCODE_E] > 0 ? true : false;
		_LMB = SDL_GetMouseState(&_mouseX, &_mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT);
		//SDL_GetMouseState(&_mouseX, &_mouseY);
	}
}
