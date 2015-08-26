#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic() : W(0), A(1), S(2), D(3), Q(4), E(5) {
}


GameLogic::~GameLogic() {
}

void GameLogic::init(GameState* gameState, GameEngine::Camera* camera, StagingManager* manager) {
	_gameState = gameState;
	_Camera = camera;
	_StagingManager = manager;
	_keys = _InputManager.getKeyPresses();
}

void GameLogic::processInput() {
	SDL_Event event;
	//_InputManager.update();
	std::vector<float> mouseCoords = _InputManager.getMouseCoords();
	//Poll every event and handle it
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		//If the user clicked the close button
		case SDL_QUIT:
			*_gameState = GameState::EXIT;
			break;
		default:
			_InputManager.update();
		}
	}

	//Handle input here
	std::vector<Button>* buttonRefs;
	Player* player;

	switch(*_gameState) {
	case GameState::MAIN_MENU:
		//std::cout << mouseCoords[0] << ", " << mouseCoords[1] << std::endl;
		buttonRefs = _StagingManager->getButtonRefs();
		//check for button clicks
		//std::cout << _InputManager.getMousePress() << std::endl;
		if(_InputManager.getMousePress()) {
			for(auto& button : *buttonRefs) {
				if(GameEngine::Collision::checkClick(*(button.getHitbox()), mouseCoords[0], mouseCoords[1])) {
					*_gameState = button.click();
					std::cout << "State change to: " << (*_gameState == GameState::PLAYING ? "playing." : *_gameState == GameState::MAIN_MENU ? "main menu." : "exit.") << std::endl;
				}
			}
		}
		break;
	case GameState::PLAYING:
		player = _StagingManager->getPlayer();
		//Temporary camera movement code
		if((_keys[D] != _keys[A]) && (_keys[W] != _keys[S])) {
			//If there is diagonal movement then normalize it so the distance moved is still player speed * 1
			player->translate(player->PLAYER_SPEED * (_keys->at(D) - _keys->at(A) / sqrt(2)), player->PLAYER_SPEED * (_keys->at(W) - _keys->at(S)) / sqrt(2));
		} else {
			//Move the player by the additions of the key presses
			player->translate(player->PLAYER_SPEED * (_keys->at(D) - _keys->at(A)), player->PLAYER_SPEED * (_keys->at(W) - _keys->at(S)));
		}
		if(abs(_keys->at(Q) - _keys->at(E))) {
			_Camera->setScale(_Camera->getScale() + _Camera->SCALE_SPEED * (_keys->at(Q) - _keys->at(E)));
		}
		break;
	default:
		break;
	}
}