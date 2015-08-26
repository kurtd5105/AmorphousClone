#pragma once
#include <vector>
#include <SDL/SDL.h>
#include <GL/glew.h>

namespace GameEngine {
	/*enum class Key {
		W = 0, A, S, D, Q, E
	};*/
	class InputManager {
	public:
		InputManager();
		~InputManager();

		void update();

		std::vector<float> getMouseCoords() { return std::vector<float>{(float)_mouseX, (float)_mouseY}; }
		bool getMousePress() { return _LMB; }

		std::vector<bool>* getKeyPresses() { return &_keyPresses; }
	private:
		const Uint8 *_keys;// = SDL_GetKeyboardState(NULL);
		std::vector<bool> _keyPresses;
		bool _LMB;
		int _mouseX, _mouseY;
	};
}
