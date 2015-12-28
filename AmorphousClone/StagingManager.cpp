#include "StagingManager.h"

StagingManager::StagingManager() : _gameState(nullptr), _SpriteManager(nullptr), _stageState(EXIT) {
}


StagingManager::~StagingManager() {
}

void StagingManager::init(GameState* gameState, GameEngine::SpriteManager* manager, GameEngine::FontBatcher* defaultFont) {
	_gameState = gameState;
	_SpriteManager = manager;
	_defaultFont = defaultFont;
	loadState();
}

void StagingManager::loadState() {
	//Return if the stage is in the correct state already
	if(*_gameState == _stageState) {
		return;
	}
	//Cleanup the sprites on screen and any buttons
	_SpriteManager->clearSprites();
	_buttons.clear();
	_player.~Player();
	/*for(auto& enemy : _enemies) {
		goople.~Goople();
	}*/
	
	Button button;
	GameEngine::Text text;
	GameEngine::Color color;
	//Setup the new sprites on screen
	switch(*_gameState) {
	case GameState::MAIN_MENU:
		button.init(300.0f, 350.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "PLAY", GameState::PLAYING, _SpriteManager);
		_buttons.push_back(button);

		button.init(300.0f, 150.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "EXIT", GameState::EXIT, _SpriteManager);
		_buttons.push_back(button);
		_stageState = *_gameState;
		break;
	case GameState::LOADING:
		_SpriteManager->addSprite(275.0f, 275.0f, 250.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/loading.png");
		break;
	case GameState::PLAYING:
		color.r = 255;
		color.g = 0;
		color.b = 0;
		color.a = 255;
		std::string test = "\"";
		for(int i = 32; i < 127; i++) {
			test += char(i);
		}
		test += "\"";
		text.init(test, glm::vec2(0, 0), glm::vec2(1, 1), 1.0f, color, _defaultFont);
		_player.init(375.0f, 275.0f, 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/player.png", _SpriteManager);
		//_SpriteManager->addSprite(0.0f, 0.0f, 160.0f, 90.0f, 1.0f, std::vector<float>{}, "Textures/01.png");
		_SpawnManager.init(800, 600, 20, _SpriteManager);
		//_SpawnManager.startSpawn();
		_stageState = *_gameState;
		break;
	}
}