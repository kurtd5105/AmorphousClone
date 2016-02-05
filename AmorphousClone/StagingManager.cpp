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
	_checkboxes.clear();
	_sliders.clear();
	_player.~Player();
	_text.clear();
	_defaultFont->cleanUp();
	
	//Create all the objects used in the stage creation
	//GameEngine::SimpleButton button;
	//GameEngine::Checkbox checkbox;
	//GameEngine::Slider slider;
	//GameEngine::Text text;
	GameEngine::Color color;
	std::function<void(void)> callback;

	//Setup the new sprites on screen
	switch(*_gameState) {
	case GameState::MAIN_MENU:
		//Set the callback to be capturing (uses _gameState passed by reference) (done with [&])
		callback = [&]() { *_gameState = GameState::PLAYING; };
		//Create the play button
		_simpleButtons.emplace_back();
		_simpleButtons.emplace_back();
		_simpleButtons.emplace_back();
		_simpleButtons[0].init(300.0f, 350.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "PLAY", callback, _SpriteManager);

		callback = [&]() { *_gameState = GameState::OPTIONS; };
		//Create the options button
		_simpleButtons[1].init(300.0f, 250.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "OPTIONS", callback, _SpriteManager);

		callback = [&]() { *_gameState = GameState::EXIT; };
		//Create the quit button
		_simpleButtons[2].init(300.0f, 150.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "QUIT", callback, _SpriteManager);

		//Empty callback
		callback = []() {};

		//Make the color blue
		color.r = 0;
		color.g = 0;
		color.b = 255;
		color.a = 255;

		//Create checkbox for testing purposes
		_checkboxes.emplace_back();
		_checkboxes[0].init(50.0f, 50.0f, 20.0f, 20.0f, 1.0f, "Textures/checkbox.png", "Animations/checkbox.ani", "Test", color, callback, _SpriteManager, _defaultFont);

		//Create slider for testing purposes
		_sliders.emplace_back();
		//_sliders[0] = new GameEngine::Slider();
		_sliders[0].init(250.0f, 50.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png", color, callback,
					_SpriteManager, _defaultFont, _InputManager);
		//_sliders.push_back(slider);

		//Set the stage state to the game state now that everything is setup
		_stageState = *_gameState;
		break;
	case GameState::LOADING:
		_SpriteManager->addSprite(275.0f, 275.0f, 250.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/loading.png");
		break;
	case GameState::PLAYING:
	{
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
		_text.emplace_back();
		_text[0].init(test, glm::vec2(0, 0), glm::vec2(1, 1), 1.0f, color, _defaultFont);

		//Create the player
		_player.init(375.0f, 275.0f, 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/player.png", _SpriteManager);

		//Begin spawning enemies
		_SpawnManager.init(800, 600, 1000, _SpriteManager);

		//Set the stage state to the game state now that everything is setup
		_stageState = *_gameState;
		break;
	}
	case GameState::OPTIONS:
		callback = [&]() { *_gameState = GameState::MAIN_MENU; };
		//Create the quit button
		_simpleButtons.emplace_back();
		_simpleButtons[0].init(300.0f, 150.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "BACK", callback, _SpriteManager);

		//Empty callback
		callback = []() {};

		//Make the color blue
		color.r = 0;
		color.g = 0;
		color.b = 255;
		color.a = 255;

		_text.emplace_back();
		_text.emplace_back();

		_text[0].init("Music Volume:", glm::vec2(20, 500), glm::vec2(1, 1), 1.0f, color, _defaultFont);
		_text[1].init("SFX Volume:", glm::vec2(20, 400), glm::vec2(1, 1), 1.0f, color, _defaultFont);

		//Create sliders for music and sfx volumes
		_sliders.emplace_back();
		_sliders.emplace_back();
		_sliders.emplace_back();
		//_sliders[0] = new GameEngine::Slider();
		//_sliders[1] = new GameEngine::Slider();
		//_sliders[2] = new GameEngine::Slider();

		_sliders[0].init(150.0f, 500.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png", color, callback,
					_SpriteManager, _defaultFont, _InputManager);
		_sliders[1].init(150.0f, 400.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png", color, callback,
					_SpriteManager, _defaultFont, _InputManager);
		_sliders[2].init(150.0f, 300.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png", color, callback,
						  _SpriteManager, _defaultFont, _InputManager);

		//Set the stage state to the game state now that everything is setup
		_stageState = *_gameState;
		break;
	}
}