#include "GameLogic.h"


GameLogic::GameLogic() {
}


GameLogic::~GameLogic() {
}

void GameLogic::init(GameState* gameState,GameEngine::Camera* camera) {
	_gameState = gameState;
	_Camera = camera;
}

void GameLogic::processInput() {
	SDL_Event event;

	//Get the pointer to the state of the keyboard key presses
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	//Poll every event and handle it
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			//If the user clicked the close button
		case SDL_QUIT:
			*_gameState = GameState::EXIT;
			break;
		}
	}

	//Handle input here

	//Temporary camera movement code
	Uint8 KEY_A = SDL_SCANCODE_A;
	Uint8 KEY_D = SDL_SCANCODE_D;
	Uint8 KEY_W = SDL_SCANCODE_W;
	Uint8 KEY_S = SDL_SCANCODE_S;
	if((keys[KEY_D] != keys[KEY_A]) && (keys[KEY_W] != keys[KEY_S])) {
		//If there is diagonal movement then normalize it so the distance moved is still camera speed * 1
		_Camera->setPosition(_Camera->getPosition() + glm::vec2(_Camera->CAMERA_SPEED * (keys[KEY_D] - keys[KEY_A]) / sqrt(2), _Camera->CAMERA_SPEED*(keys[KEY_W] - keys[KEY_S]) / sqrt(2)));
	} else {
		//Move the camera by the additions of the key presses
		_Camera->setPosition(_Camera->getPosition() + glm::vec2(_Camera->CAMERA_SPEED * (keys[KEY_D] - keys[KEY_A]), _Camera->CAMERA_SPEED*(keys[KEY_W] - keys[KEY_S])));
	}
	_Camera->setScale(_Camera->getScale() + _Camera->SCALE_SPEED * (keys[SDL_SCANCODE_Q] - keys[SDL_SCANCODE_E]));
}