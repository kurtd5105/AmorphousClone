#include "StagingManager.h"
#include <iostream>

StagingManager::StagingManager() : _gameState(nullptr), _SpriteManager(nullptr), _stageState(EXIT) {
}


StagingManager::~StagingManager() {
}

void StagingManager::init(GameState* gameState, GameEngine::Options* options, GameEngine::SpriteManager* manager,
						  GameEngine::FontBatcher* defaultFont, GameEngine::InputManager* inputManager) {
	_gameState = gameState;
	_SpriteManager = manager;
	_InputManager = inputManager;
	_defaultFont = defaultFont;
	_options = options;
	loadState();
}

void StagingManager::loadState() {
	//Return if the stage is in the correct state already
	if(*_gameState == _stageState) {
		return;
	}
	//Cleanup the stage
	_SpriteManager->clearSprites();
	_simpleButtons.clear();
	_checkboxes.clear();
	_sliders.clear();
	_selectionBoxes.clear();
	_player.~Player();
	_text.clear();
	_defaultFont->cleanUp();
	
	GameEngine::Color color;
	std::function<void(void)> callback;

	//Setup the new stage
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
		_sliders[0].init(250.0f, 50.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, 0.0f, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png", color, callback,
					_SpriteManager, _defaultFont, _InputManager, std::pair<int, int>(100, 1000));

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
	{
		//Empty callback
		callback = []() {};

		//Make the color blue
		color.r = 0;
		color.g = 0;
		color.b = 255;
		color.a = 255;

		_text.emplace_back();
		_text.emplace_back();
		_text.emplace_back();
		_text.emplace_back();
		_text.emplace_back();

		_text[0].init("Music Volume:", glm::vec2(20, 500), glm::vec2(1, 1), 1.0f, color, _defaultFont);
		_text[1].init("SFX Volume:", glm::vec2(20, 400), glm::vec2(1, 1), 1.0f, color, _defaultFont);
		_text[2].init("Spawn Count:", glm::vec2(500, 500), glm::vec2(1, 1), 1.0f, color, _defaultFont);
		_text[3].init("Spawn Rate:", glm::vec2(500, 400), glm::vec2(1, 1), 1.0f, color, _defaultFont);
		_text[4].init("Resolution:", glm::vec2(225, 300), glm::vec2(1, 1), 1.0f, color, _defaultFont);

		//Create sliders for music and sfx volumes
		_sliders.emplace_back();
		_sliders.emplace_back();
		_sliders.emplace_back();
		_sliders.emplace_back();

		//Music Volume
		_sliders[0].init(150.0f, 500.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, _options->music * 100, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png",
						 color, callback, _SpriteManager, _defaultFont, _InputManager);
		//SFX Volume
		_sliders[1].init(150.0f, 400.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, _options->sfx * 100, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png",
						 color, callback, _SpriteManager, _defaultFont, _InputManager);
		//Spawn Count
		_sliders[2].init(620.0f, 500.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, 0.0f, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png", color, callback,
						 _SpriteManager, _defaultFont, _InputManager);
		//Spawn Rate
		_sliders[3].init(620.0f, 400.0f, 10.0f, 20.0f, 100.0f, 7.0f, 1.0f, 0.0f, "Textures/slider.png", "Animations/slider.ani", "Textures/line.png", color, callback,
						 _SpriteManager, _defaultFont, _InputManager);

		callback = [&]() {
			_options->music = _sliders[0].getPercent() / 100.0f;
			_options->sfx = _sliders[1].getPercent() / 100.0f;
			*_gameState = GameState::MAIN_MENU;
		};
		//Create the back button
		_simpleButtons.emplace_back();
		_simpleButtons[0].init(300.0f, 150.0f, 200.0f, 50.0f, 1.0f, "Textures/buttons.png", "Animations/buttons.ani", "BACK", callback, _SpriteManager);

		std::function<void(void)> callbackLeft;
		std::function<void(void)> callbackRight;

		_selectionBoxes.emplace_back();

		callbackLeft = [&]() {
			_selectionBoxes[0].backward();
		};
		callbackRight = [&]() {
			_selectionBoxes[0].forward();
		};

		//Create a vector containing the possible screen resolutions in the format WIDTHxHEIGHT
		std::ostringstream oss;
		std::vector<std::string> resolutions;
		unsigned int max = std::to_string(validWidths.back()).length() + std::to_string(validHeights.back()).length() + 1;
		unsigned int curr = 0;
		std::string temp;
		for(unsigned int i = 0; i < validWidths.size(); i++) {
			oss.clear();
			oss.str("");
			oss << validWidths[i] << "x" << validHeights[i];

			//Try to center the string
			oss.seekp(0);
			temp = oss.str();
			curr = temp.length();
			oss.clear();
			oss.str("");
			for(unsigned int i = 0; i < (unsigned int)((max - curr) * 1.5f); i++) {
				oss << " ";
			}
			oss << temp;
			resolutions.push_back(oss.str());
		}

		_selectionBoxes[0].init(333.3f, 300.0f, 25.0f, 25.0f, 85.0f, 1.0f, resolutions, "LEFT", "RIGHT", "Textures/arrows.png", "Animations/arrows.ani",
								"Textures/arrows.png", "Animations/arrows.ani", color, callbackLeft, callbackRight, _SpriteManager, _defaultFont);

		//Set the stage state to the game state now that everything is setup
		_stageState = *_gameState;
		break;
	}
	}
}