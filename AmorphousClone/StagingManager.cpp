#include "StagingManager.h"

StagingManager::StagingManager() : _gameState(nullptr), _SpriteManager(nullptr) {
}


StagingManager::~StagingManager() {
}

void StagingManager::init(GameState* gameState, GameEngine::SpriteManager* manager) {
	_gameState = gameState;
	_SpriteManager = manager;
	loadState();
}

void StagingManager::loadState() {
	//Cleanup the sprites on screen and any buttons
	_SpriteManager->clearSprites();
	_buttons.clear();
	Button button;
	//Setup the new sprites on screen
	switch(*_gameState) {
	case GameState::MAIN_MENU:
		button.init(300.0f, 350.0f, 200.0f, 50.0f, 1.0f, std::vector<float>{0.0f, 1.0f, 0.5f, 1.0f}, "Textures/buttons.png", GameState::PLAYING, _SpriteManager);
		_buttons.push_back(button);

		button.init(300.0f, 150.0f, 200.0f, 50.0f, 1.0f, std::vector<float>{0.0f, 1.0f, 0.0f, 0.5f}, "Textures/buttons.png", GameState::EXIT, _SpriteManager);
		_buttons.push_back(button);

		break;
	case GameState::PLAYING:
		break;
	}
}