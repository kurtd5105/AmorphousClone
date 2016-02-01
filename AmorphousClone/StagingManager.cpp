#include "StagingManager.h"
#include <iostream>

StagingManager::StagingManager() : _gameState(nullptr), _SpriteManager(nullptr), _stageState(EXIT) {
}


StagingManager::~StagingManager() {
}

void StagingManager::init(GameState* gameState, GameEngine::SpriteManager* manager, GameEngine::FontBatcher* defaultFont, GameEngine::InputManager* inputManager) {
	_gameState = gameState;
	_SpriteManager = manager;
	_InputManager = inputManager;
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
	_simpleButtons.clear();
	_player.~Player();
	_defaultFont->cleanUp();
	
	//Create all the objects used in the stage creation
	GameEngine::SimpleButton button;
	GameEngine::Checkbox checkbox;
	GameEngine::Slider slider;
	GameEngine::Text text;
	GameEngine::Color color;
	std::function<void(void)> callback;

	//Setup the new sprites on screen
	switch(*_gameState) {
	case GameState::MAIN_MENU:
		//Set the callback to be capturing (uses _gameState passed by reference) (done with [&])
		callback = [&]() { *_gameState = GameState::PLAYING; };
		//Create the play button
		button.init(300.0f, 350.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "PLAY", callback, _SpriteManager);
		_simpleButtons.push_back(button);

		callback = []() {};//callback = [&]() { *_gameState = GameState::OPTIONS; };
		//Create the options button
		button.init(300.0f, 250.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "OPTIONS", callback, _SpriteManager);
		_simpleButtons.push_back(button);

		callback = [&]() { *_gameState = GameState::EXIT; };
		//Create the quit button
		button.init(300.0f, 150.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "QUIT", callback, _SpriteManager);
		_simpleButtons.push_back(button);

		//Empty callback
		callback = []() {};

		//Make the color blue
		color.r = 0;
		color.g = 0;
		color.b = 255;
		color.a = 255;

		//Create checkbox for testing purposes
		checkbox.init(50.0f, 50.0f, 20.0f, 20.0f, 1.0f, "Textures/checkbox.png", "Animations/checkbox.ani", "Test", color, callback, _SpriteManager, _defaultFont);
		_checkboxes.push_back(checkbox);

		//Create slider for testing purposes
		slider.init(250.0f, 50.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png", color, callback,
					_SpriteManager, _defaultFont, _InputManager);
		_sliders.push_back(slider);

		//Set the stage state to the game state now that everything is setup
		_stageState = *_gameState;
		break;
	case GameState::LOADING:
		_SpriteManager->addSprite(275.0f, 275.0f, 250.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/loading.png");
		break;
	case GameState::PLAYING:
		//Make the color red
		color.r = 255;
		color.g = 0;
		color.b = 0;
		color.a = 255;

		//Create a test string of all the characters
		std::string test = "\"";
		for(int i = 32; i < 127; i++) {
			test += char(i);
		}
		test += "\"";
		text.init(test, glm::vec2(0, 0), glm::vec2(1, 1), 1.0f, color, _defaultFont);

		//Create the player
		_player.init(375.0f, 275.0f, 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/player.png", _SpriteManager);

		//Begin spawning enemies
		_SpawnManager.init(800, 600, 1000, _SpriteManager);

		//Set the stage state to the game state now that everything is setup
		_stageState = *_gameState;
		break;
	}
}