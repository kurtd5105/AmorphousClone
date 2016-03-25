#pragma once
#include <vector>

#include <SDL/SDL.h>
#include <glm/glm.hpp>

namespace GameEngine {
	/*enum class Key {
		W = 0, A, S, D, Q, E
	};*/
	class InputManager {
	public:
		InputManager();
		~InputManager();

		void update();

		glm::vec2 getMouseCoords() const { return glm::vec2(float(_mouseX), float(_mouseY)); }
		bool getMousePress() const { return _LMB; }

		std::vector<bool>* getKeyPresses() { return &_keyPresses; }
	private:
		const Uint8 *_keys;// = SDL_GetKeyboardState(NULL);
		std::vector<bool> _keyPresses;
		bool _LMB;
		int _mouseX, _mouseY;
	};
}
