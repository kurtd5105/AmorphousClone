#include "GameLogic.h"
#include <GameEngine/CollisionManager.h>

//#include <iostream>

GameLogic::GameLogic() : _InputManager(nullptr), _Camera(nullptr), _StagingManager(nullptr), _SpawnManager(nullptr), _gameState(nullptr),
_keys(nullptr), _simpleButtonRefs(nullptr), _checkboxRefs(nullptr), _sliderRefs(nullptr), _selectionRefs(nullptr),
_currClicked(nullptr), _player(nullptr), _enemies(nullptr),
W(0), A(1), S(2), D(3), Q(4), E(5), _clickHold(false){}


GameLogic::~GameLogic() {
	_enemies = nullptr;
}

void GameLogic::init(GameState* gameState, GameEngine::Camera* camera, StagingManager* manager, GameEngine::InputManager* inputManager) {
	_gameState = gameState;
	_Camera = camera;
	_StagingManager = manager;
	_InputManager = inputManager;
	_keys = _InputManager->getKeyPresses();
}

void GameLogic::getStage() {
	//Get the stage in its current state from the stage, the stage must be updated first
	switch(_StagingManager->getStageState()) {
	case GameState::MAIN_MENU:
		_simpleButtonRefs = _StagingManager->getSimpleButtonRefs();
		_checkboxRefs = _StagingManager->getCheckboxRefs();
		_sliderRefs = _StagingManager->getSliderRefs();
		_selectionRefs = _StagingManager->getSelectionRefs();
		break;
	case GameState::OPTIONS:
		_simpleButtonRefs = _StagingManager->getSimpleButtonRefs();
		_checkboxRefs = _StagingManager->getCheckboxRefs();
		_sliderRefs = _StagingManager->getSliderRefs();
		_selectionRefs = _StagingManager->getSelectionRefs();
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

void GameLogic::updateEnemy(float step) const {
	for(auto& enemy : *_enemies) {
		//enemy.moveTo(_player);
		enemy.moveToTarget(step);
	}
}

void GameLogic::collisionAgents() const {

	//Player collision with enemies
	for (auto& enemy : *_enemies) {	
		_player->collideAgents(&enemy);
	}

	//Enemy collisions
	for (auto& enemy : *_enemies) {
		if (enemy.isEnabled()) {
			for (auto& enemy2 : *_enemies) {
				if (&enemy != &enemy2 && enemy2.isEnabled()) {
					enemy.collideAgents(&enemy2);
				}
			}
		}
	}
}

void GameLogic::processInput(float step) {
	SDL_Event event;
	//_InputManager.update();
	auto mouseCoords = _InputManager->getMouseCoords();

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

	_InputManager->update();
	getStage();
	//Update the game based on the stage state, the stage is updated first so the game logic
	//cannot be applied before the correct stage is applied
	switch(_StagingManager->getStageState()) {
	case GameState::MAIN_MENU:
		checkButtons(mouseCoords);
		break;
	case GameState::OPTIONS:
		checkButtons(mouseCoords);
		break;
	case GameState::PLAYING:
	{

		collisionAgents();

		_SpawnManager->spawn();

		//Check if A or D and W or S are pressed for diagonal movement
		if((_keys->at(D) != _keys->at(A)) && (_keys->at(W) != _keys->at(S))) {
			//If there is diagonal movement then normalize it so the distance moved is still player speed * 1
			_player->translate(_player->PLAYER_SPEED * float(_keys->at(D) - _keys->at(A)) / sqrt(2.0f), 
							   _player->PLAYER_SPEED * float(_keys->at(W) - _keys->at(S)) / sqrt(2.0f),
							   step);
		} else {
			//Move the player by the additions of the key presses
			_player->translate(_player->PLAYER_SPEED * (_keys->at(D) - _keys->at(A)), _player->PLAYER_SPEED * (_keys->at(W) - _keys->at(S)), step);
		}
		if(_keys->at(Q) != _keys->at(E)) {
			_Camera->setScale(_Camera->getScale() + _Camera->SCALE_SPEED * (_keys->at(Q) - _keys->at(E)));
			//_player->rotate((_keys->at(Q) - _keys->at(E)) * 0.01f);
		}
		_player->pointAt(_Camera->toWorldCoords(mouseCoords));

		updateEnemy(step);

		break;
	}
	default:
		break;
	}
}

void GameLogic::checkButtons(glm::vec2& mouseCoords) {
	mouseCoords = _Camera->toWorldCoords(mouseCoords);
	//Check to see if the mouse is clicked
	if(_InputManager->getMousePress()) {
		//If the mouse is clicked, check to see if it is being held or not and on what button
		if(!_clickHold) {
			//If this is the first frame that a button is being clicked, set the clicked button
			for(auto& button : *_simpleButtonRefs) {
				if(GameEngine::Collision::checkClick(*(button.getHitbox()), mouseCoords[0], mouseCoords[1])) {
					_currClicked = &button;
				}
			}
			for(auto& button : *_checkboxRefs) {
				if(GameEngine::Collision::checkClick(*(button.getHitbox()), mouseCoords[0], mouseCoords[1])) {
					_currClicked = &button;
				}
			}
			for(auto& button : *_sliderRefs) {
				if(GameEngine::Collision::checkClick(*(button.getHitbox()), mouseCoords[0], mouseCoords[1])) {
					_currClicked = &button;
				}
			}
			for(auto& button : *_selectionRefs) {
				if(GameEngine::Collision::checkClick(*(button.getLeft()->getHitbox()), mouseCoords[0], mouseCoords[1])) {
					_currClicked = button.getLeft();
				} else if(GameEngine::Collision::checkClick(*(button.getRight()->getHitbox()), mouseCoords[0], mouseCoords[1])) {
					_currClicked = button.getRight();
				}
			}
		} else {
			//If the mouse button is being held and it was clicking a button
			if(_currClicked != nullptr) {
				_currClicked->onPush();
			}
		}
		_clickHold = true;
	} else {
		//If the mouse button isn't being pressed
		_clickHold = false;

		//If there was a button that was being pressed then click it if the mouse is still over it
		if(_currClicked != nullptr) {
			_currClicked->onIdle();
			if(GameEngine::Collision::checkClick(*(_currClicked->getHitbox()), mouseCoords[0], mouseCoords[1])) {
				_currClicked->onClick()();
			}
			_currClicked = nullptr;
		}

		//Check to see if the mouse is hovering over a button or not
		for(auto& button : *_simpleButtonRefs) {
			if(GameEngine::Collision::checkClick(*(button.getHitbox()), mouseCoords[0], mouseCoords[1])) {
				button.onHover();
			} else {
				button.onIdle();
			}
		}
		for(auto& button : *_checkboxRefs) {
			if(GameEngine::Collision::checkClick(*(button.getHitbox()), mouseCoords[0], mouseCoords[1])) {
				button.onHover();
			} else {
				button.onIdle();
			}
		}
		for(auto& button : *_sliderRefs) {
			if(GameEngine::Collision::checkClick(*(button.getHitbox()), mouseCoords[0], mouseCoords[1])) {
				button.onHover();
			} else {
				button.onIdle();
			}
		}
		for(auto& button : *_selectionRefs) {
			if(GameEngine::Collision::checkClick(*(button.getLeft()->getHitbox()), mouseCoords[0], mouseCoords[1])) {
				button.getLeft()->onHover();
			} else {
				button.getLeft()->onIdle();
			}
			if(GameEngine::Collision::checkClick(*(button.getRight()->getHitbox()), mouseCoords[0], mouseCoords[1])) {
				button.getRight()->onHover();
			} else {
				button.getRight()->onIdle();
			}
		}
	}
}