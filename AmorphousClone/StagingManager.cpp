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
	//Cleanup the sprites on screen
	_SpriteManager->clearSprites();

	//Setup the new sprites on screen
	switch(*_gameState) {
	case GameState::MAIN_MENU:
		//Eventually to be replaced with button classes
		_SpriteManager->addSprite(300.0f, 350.0f, 200.0f, 50.0f, 1.0f, std::vector<float>{0.0f, 0.5f}, std::vector<float>{1.0f, 1.0f}, "Textures/buttons.png");
		_SpriteManager->addSprite(300.0f, 150.0f, 200.0f, 50.0f, 1.0f, std::vector<float>{0.0f, 0.0f}, std::vector<float>{1.0f, 0.5f}, "Textures/buttons.png");
		break;
	case GameState::PLAYING:
		_player.init(375.0f, 275.0f, 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/player.png", _SpriteManager);
		break;
	}
}