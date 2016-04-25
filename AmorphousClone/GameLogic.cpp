#include "GameLogic.h"
#include <GameEngine/CollisionManager.h>
#include <iostream>

//#include <iostream>

GameLogic::GameLogic() : _InputManager(nullptr), _Camera(nullptr), _StagingManager(nullptr), _SpawnManager(nullptr), _gameState(nullptr),
_keys(nullptr), _simpleButtonRefs(nullptr), _checkboxRefs(nullptr), _sliderRefs(nullptr), _selectionRefs(nullptr), _textRefs(nullptr),
_currClicked(nullptr), _player(nullptr), _enemies(nullptr), W(0), A(1), S(2), D(3), Q(4), E(5), _gloopleKills(0), _biterKills(0), _meltieKills(0),
_stickieKills(0), _score(0), _gloopleSwing(0), _biterSwing(0), _meltieSwing(0), _stickieSwing(0), _clickHold(false){}


GameLogic::~GameLogic() {
	_enemies = nullptr;
	for(auto& g : _goos) {
		delete g;
	}
}

void GameLogic::init(GameState* gameState, GameEngine::Camera* camera, StagingManager* manager, GameEngine::InputManager* inputManager) {
	_gameState = gameState;
	_curr = *gameState;
	_Camera = camera;
	_StagingManager = manager;
	_InputManager = inputManager;
	_keys = _InputManager->getKeyPresses();
}

void GameLogic::getStage() {
	if(_curr != *_gameState) {
		for(auto& g : _goos) {
			delete g;
		}
		_goos.clear();
		_curr = *_gameState;
	}
	
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
		_textRefs = _StagingManager->getText();
		break;
	case GameState::AWARDS:
		_simpleButtonRefs = _StagingManager->getSimpleButtonRefs();
		break;
	case GameState::REWARDS:
		_simpleButtonRefs = _StagingManager->getSimpleButtonRefs();
		break;
	case GameState::WON:
		_simpleButtonRefs = _StagingManager->getSimpleButtonRefs();
		break;
	case GameState::LOST:
		_simpleButtonRefs = _StagingManager->getSimpleButtonRefs();
		break;
	default:
		break;
	}
}

void GameLogic::updateEnemy(float step) {
	for(auto& enemy : *_enemies) {
		//enemy.moveTo(_player);
		enemy.moveToTarget(step);
		enemy.processTimers(step);
	}

	for(auto& g : _goos) {
		if(g != nullptr) {
			g->fade(step);
		} else {
			//std::cout << "Bad goo pointer." << std::endl;
		}
	}
	while(_goos.size() > 0 && !_goos.front()->isAlive()) {
		delete _goos.front();
		_goos.pop_front();
	}
}

void GameLogic::collisionAgents() {
	glm::vec2 tempTarget;

	//Player collision with enemies
	for(auto& enemy : *_enemies) {
		if(enemy.isEnabled()) {
			if(_player->collideAgents(&enemy)) {
				switch(enemy.getType()) {
				case GOOPLE:
					if(!_player->isInvincible()) {
						_player->onCollide(enemy.getType(), enemy.getRotation());
					}
					enemy.setTarget(glm::vec2(_player->getPos().x + 10000 * cos(enemy.getRotation() - M_PI),
						_player->getPos().y + 10000 * sin(enemy.getRotation() - M_PI)));
					break;
				case STICKIE:
					enemy.kill();
					if(enemy.hasGoo()) {
						_goos.push_back(enemy.getGoo());
					}
					if(!_player->isInvincible()) {
						_player->onCollide(enemy.getType(), enemy.getRotation());
					}
					break;
				case STICKIE_GOO:
					_player->onCollide(enemy.getType(), enemy.getRotation());
					break;
				}
			}
		}
	}

	//Sword collision with enemies
	Sword* sword = _player->getSword();
	if(sword->isActive()) {
		for(auto& enemy : *_enemies) {
			if(enemy.isEnabled()) {
				//!!!--------------------Replace with hitbox implementation--------------------!!!
				//!!!--------------------Replace with hitbox implementation--------------------!!!
				//!!!--------------------Replace with hitbox implementation--------------------!!!
				if(sword->collideAgents(&enemy)) {
					switch(enemy.getType()) {
					case GOOPLE:
						_gloopleSwing++;
						break;
					case STICKIE:
						_stickieSwing++;
						break;
					case STICKIE_GOO:
						break;
					}
					enemy.kill();
				}
			}
		}
	} else {
		_score += (_gloopleSwing + _biterSwing * 8 + _meltieSwing * 10 + _stickieSwing * 3) * (_gloopleSwing + _biterSwing + _meltieSwing + _stickieSwing);
		_gloopleKills += _gloopleSwing;
		_biterKills += _biterSwing;
		_meltieKills += _meltieSwing;
		_stickieKills += _stickieSwing;
		_gloopleSwing = _biterSwing = _meltieSwing = _stickieSwing = 0;
	}
	
	//Enemy collisions
	int goopleCount, stickieCount;
	for (auto& enemy : *_enemies) {
		if (enemy.isEnabled()) {

			for (auto& enemy2 : *_enemies) {
				goopleCount = stickieCount = 0;

				if (&enemy != &enemy2 && enemy2.isEnabled()) {
					if (enemy.collideAgents(&enemy2) && !enemy.getCollided() && !enemy2.getCollided()) {

						//countEnemy(enemy, &goopleCount, &stickieCount);
						//countEnemy(enemy2, &goopleCount, &stickieCount);
						if(enemy.getType() == GOOPLE && enemy2.getType() == GOOPLE) {
							goopleCount = 2;
						}

						if(goopleCount == 2) {
							enemy.setCollided(true);
							enemy2.setCollided(true);
							tempTarget = enemy.getTarget();
							enemy.setTarget(enemy2.getTarget());
							enemy2.setTarget(tempTarget);
						}
						
					}
				}
			}
		}
	}
	for (auto& enemy : *_enemies) {
		enemy.setCollided(false);
	}
}

void GameLogic::countEnemy(EnemySuper enemy, int* goopleCount, int* stickieCount) {
	if(enemy.getType() == GOOPLE) {
		*goopleCount = *goopleCount + 1;
	} else if(enemy.getType() == STICKIE) {
		*stickieCount = *stickieCount + 1;
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

		//If the player is dead
		if(!_player->isAlive()) {
			*_gameState = LOST;
			break;
		}

		//If the spawn manager is done spawning
		if(!_SpawnManager->spawn()) {
			auto win = true;
			for(auto& enemy : *_enemies) {
				if(enemy.isEnabled()) {
					win = false;
					break;
				}
			}
			if(win) {
				*_gameState = WON;
				break;
			}
		}

		(*_textRefs)[0].changeText("Enemies Remaining: " + std::to_string(_SpawnManager->getEnemiesRemaining()));
		(*_textRefs)[1].changeText("Score: " + std::to_string(_score));

		if(_player->isEnabled() && !_player->isKnockback() && !_player->getSword()->isActive()) {
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
			/*if(_keys->at(Q) != _keys->at(E)) {
				_Camera->setScale(_Camera->getScale() + _Camera->SCALE_SPEED * (_keys->at(Q) - _keys->at(E)));
				//_player->rotate((_keys->at(Q) - _keys->at(E)) * 0.01f);
				}*/
			_player->pointAt(_Camera->toWorldCoords(mouseCoords));

			if(_InputManager->getMousePress()) {
				if(!_player->getSword()->isActive()) {
					_player->getSword()->setActive();
				}
			}
		} else if(_player->isKnockback()) {
			_player->knockback(step);
		} else if(_player->getSword()->isActive()) {
			_player->getSword()->attack(step);
			_player->rotate(_player->getRotation());
		}
		_player->processTimers(step);
		//std::cout << "Knockback: " << (_player->isKnockback() ? "yes" : "no") << "; Invincible: " << (_player->isInvincible() ? "yes." : "no.") << std::endl;

		updateEnemy(step);

		break;
	}
	case GameState::AWARDS:
		checkButtons(mouseCoords);
		break;
	case GameState::REWARDS:
		checkButtons(mouseCoords);
		break;
	case GameState::LOST:
		checkButtons(mouseCoords);
		break;
	case GameState::WON:
		checkButtons(mouseCoords);
		break;
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