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

void GameLogic::getStage() {
	switch(*_gameState) {
	case GameState::MAIN_MENU:
		_buttonRefs = _StagingManager->getButtonRefs();
		break;
	case GameState::PLAYING:
		_SpawnManager = _StagingManager->getSpawnManager();
		_player = _StagingManager->getPlayer();
		_enemies = _SpawnManager->getEnemies();
		break;
	default:
		break;
	}
}

void GameLogic::updateEnemy() {
	for(auto& enemy : *_enemies) {
		enemy.moveTo(_player);
	}
}

void GameLogic::processInput() {
	SDL_Event event;
	//_InputManager.update();
	glm::vec2 mouseCoords = _InputManager.getMouseCoords();
	auto output = _Camera->toWorldCoords(mouseCoords);
	//Poll every event and handle it
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		//If the user clicked the close button
		case SDL_QUIT:
			*_gameState = GameState::EXIT;
			break;
		default:
			break;
		}
	}

	_InputManager.update();
	getStage();
	switch(*_gameState) {
	case GameState::MAIN_MENU:
		//std::cout << mouseCoords[0] << ", " << mouseCoords[1] << std::endl;
		//check for button clicks
		//std::cout << _InputManager.getMousePress() << std::endl;
		if(_InputManager.getMousePress()) {
			for(auto& button : *_buttonRefs) {
				if(GameEngine::Collision::checkClick(*(button.getHitbox()), mouseCoords[0], mouseCoords[1])) {
					*_gameState = button.click();
					std::cout << "State change to: " << (*_gameState == GameState::PLAYING ? "playing." : *_gameState == GameState::MAIN_MENU ? "main menu." : "exit.") << std::endl;
				}
			}
		}
		break;
	case GameState::PLAYING:
	{
		//_SpawnManager->startSpawn();
		//Check if A or D and W or S are pressed for diagonal movement
		if((_keys->at(D) != _keys->at(A)) && (_keys->at(W) != _keys->at(S))) {
			//If there is diagonal movement then normalize it so the distance moved is still player speed * 1
			_player->translate(_player->PLAYER_SPEED * (float)(_keys->at(D) - _keys->at(A)) / sqrt(2.0f), _player->PLAYER_SPEED * (float)(_keys->at(W) - _keys->at(S)) / sqrt(2.0f));
		} else {
			//Move the player by the additions of the key presses
			_player->translate(_player->PLAYER_SPEED * (_keys->at(D) - _keys->at(A)), _player->PLAYER_SPEED * (_keys->at(W) - _keys->at(S)));
		}
		if(_keys->at(Q) != _keys->at(E)) {
			_Camera->setScale(_Camera->getScale() + _Camera->SCALE_SPEED * (_keys->at(Q) - _keys->at(E)));
			//_player->rotate((_keys->at(Q) - _keys->at(E)) * 0.01f);
		}
		_player->pointAt(_Camera->toWorldCoords(mouseCoords));
		updateEnemy();
		break;
	}
	default:
		break;
	}
}