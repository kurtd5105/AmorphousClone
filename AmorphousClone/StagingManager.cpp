#include "StagingManager.h"
#include <sstream>


StagingManager::StagingManager() : _ResourceManager(nullptr), _SpriteManager(nullptr), _InputManager(nullptr), _defaultFont(nullptr), _options(nullptr),
_player(nullptr), _SpawnManager(nullptr), _gameState(nullptr), _stageState(EXIT) {}


StagingManager::~StagingManager() {
	if(_player != nullptr) {
		delete _player;
	}
	if(_SpawnManager != nullptr) {
		delete _SpawnManager;
	}
}

void StagingManager::init(GameState* gameState, GameEngine::Options* options, glm::vec2 scalingFactors, GameEngine::ResourceManager* resourceManager,
						  GameEngine::SpriteManager* spriteManager, GameEngine::FontBatcher* defaultFont, GameEngine::InputManager* inputManager) {
	_gameState = gameState;
	_ResourceManager = resourceManager;
	_SpriteManager = spriteManager;
	_InputManager = inputManager;
	_defaultFont = defaultFont;
	_options = options;
	_scalingFactors = scalingFactors;
	_titleFont.init("Fonts/OpenSans-Regular.ttf", 64, _ResourceManager);
	_descriptionFont.init("Fonts/OpenSans-Regular.ttf", 32, _ResourceManager);
	_fonts.push_back(&_titleFont);
	_fonts.push_back(&_descriptionFont);
	_fonts.push_back(_defaultFont);
	loadState();
}

void StagingManager::loadState() {
	//Return if the stage is in the correct state already
	if(*_gameState == _stageState) {
		return;
	}
	if(_player != nullptr) {
		delete _player;
		_player = nullptr;
	}
	if(_SpawnManager != nullptr) {
		delete _SpawnManager;
		_SpawnManager = nullptr;
	}
	//Cleanup the stage
	_SpriteManager->clearSprites();
	_simpleButtons.clear();
	_checkboxes.clear();
	_sliders.clear();
	_selectionBoxes.clear();
	_text.clear();
	_defaultFont->cleanUp();
	
	/*if(_player.isInit()) {
		_player.disable();
		_player.setInvisible();
	}*/
	
	GameEngine::Color color;
	std::function<void(void)> callback;

	//Setup the new stage
	switch(*_gameState) {
	case GameState::MAIN_MENU:
		_simpleButtons.emplace_back();
		_simpleButtons.emplace_back();
		_simpleButtons.emplace_back();
		_simpleButtons.emplace_back();
		_simpleButtons.emplace_back();

		//Set the callback to be capturing (uses _gameState passed by reference) (done with [&])
		callback = [&]() { *_gameState = GameState::PLAYING; };
		//Create the play button
		_simpleButtons[0].init(540.0f * _scalingFactors.x, 535.0f * _scalingFactors.y, 200.0f * _scalingFactors.x, 50.0f  * _scalingFactors.y,
							   1.0f, "Textures/buttons.png", "Animations/buttons.ani", "PLAY", callback, _SpriteManager);

		callback = [&]() { *_gameState = GameState::OPTIONS; };
		//Create the options button
		_simpleButtons[1].init(540.0f * _scalingFactors.x, 435.0f * _scalingFactors.y, 200.0f * _scalingFactors.x, 50.0f  * _scalingFactors.y,
							   1.0f, "Textures/buttons.png", "Animations/buttons.ani", "OPTIONS", callback, _SpriteManager);

		callback = [&]() { *_gameState = GameState::AWARDS; };
		//Create the awards button
		_simpleButtons[2].init(540.0f * _scalingFactors.x, 335.0f * _scalingFactors.y, 200.0f * _scalingFactors.x, 50.0f  * _scalingFactors.y,
							   1.0f, "Textures/buttons.png", "Animations/buttons.ani", "AWARDS", callback, _SpriteManager);

		callback = [&]() { *_gameState = GameState::REWARDS; };
		//Create the awards button
		_simpleButtons[3].init(540.0f * _scalingFactors.x, 235.0f * _scalingFactors.y, 200.0f * _scalingFactors.x, 50.0f  * _scalingFactors.y,
							   1.0f, "Textures/buttons.png", "Animations/buttons.ani", "REWARDS", callback, _SpriteManager);

		callback = [&]() { *_gameState = GameState::EXIT; };
		//Create the quit button
		_simpleButtons[4].init(540.0f * _scalingFactors.x, 135.0f * _scalingFactors.y, 200.0f * _scalingFactors.x, 50.0f  * _scalingFactors.y,
							   1.0f, "Textures/buttons.png", "Animations/buttons.ani", "QUIT", callback, _SpriteManager);

		//Empty callback
		callback = []() {};

		//Make the color blue
		color = GameEngine::COLOR::BLUE;

		//Create checkbox for testing purposes
		_checkboxes.emplace_back();
		_checkboxes[0].init(50.0f * _scalingFactors.x, 50.0f * _scalingFactors.y, 20.0f * _scalingFactors.x, 20.0f * _scalingFactors.y,
							1.0f, _scalingFactors, "Textures/checkbox.png", "Animations/checkbox.ani", "Test", color, callback, _SpriteManager, _defaultFont);

		//Create slider for testing purposes
		_sliders.emplace_back();
		_sliders[0].init(250.0f * _scalingFactors.x, 50.0f * _scalingFactors.y, 10.0f * _scalingFactors.x, 20.0f * _scalingFactors.y,
						 100.0f * _scalingFactors.x, 7.0f * _scalingFactors.y, 1.0f, _scalingFactors, 100.0f, "Textures/slider.png", "Animations/slider.ani",
						 "Textures/line.png", color, callback, _SpriteManager, _defaultFont, _InputManager, std::pair<int, int>(100, 1000));

		//Set the stage state to the game state now that everything is setup
		_stageState = *_gameState;
		break;
	case GameState::LOADING:
		_SpriteManager->addSprite(515.0f * _scalingFactors.x, 335.0f * _scalingFactors.y, 250.0f * _scalingFactors.x, 50.0f * _scalingFactors.y,
								  1.0f, std::vector<float>{}, "Textures/loading.png");
		break;
	case GameState::PLAYING:
	{
		_SpriteManager->addSprite(0.0f, 0.0f, 1920.0f, 1080.0f, 100.0f, std::vector<float>{}, "Textures/gravel.png");

		//Make the color red
		color = GameEngine::COLOR::RED;

		//Create a test string of all the characters
		std::string test = "\"";
		for(int i = 32; i < 127; i++) {
			test += char(i);
		}
		test += "\"";
		_text.emplace_back();
		_text[0].init(test, glm::vec2(0, 0), _scalingFactors, 1.0f, color, _defaultFont);

		//Create the player
		_player = new Player();
		_player->init(615.0f * _scalingFactors.x, 335.0f * _scalingFactors.y, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y,
					  1.0f, _scalingFactors, std::vector<float>{}, "Textures/player.png", _SpriteManager);

		//Begin spawning enemies
		_SpawnManager = new SpawnManager();
		_SpawnManager->init(_options->width, _options->height, _scalingFactors, _options->spawnCount, _SpriteManager);

		//Set the stage state to the game state now that everything is setup
		_stageState = *_gameState;
		break;
	}
	case GameState::OPTIONS:
	{
		//Empty callback
		callback = []() {};

		//Make the color blue
		color = GameEngine::COLOR::BLUE;

		_text.emplace_back();
		_text.emplace_back();
		_text.emplace_back();
		_text.emplace_back();
		_text.emplace_back();
		_text.emplace_back();

		_text[0].init("Music Volume:", glm::vec2(220 * _scalingFactors.x, 600 * _scalingFactors.y), _scalingFactors, 1.0f, color, _defaultFont);
		_text[1].init("SFX Volume:", glm::vec2(220 * _scalingFactors.x, 450 * _scalingFactors.y), _scalingFactors, 1.0f, color, _defaultFont);
		_text[2].init("Spawn Count:", glm::vec2(700 * _scalingFactors.x, 600 * _scalingFactors.y), _scalingFactors, 1.0f, color, _defaultFont);
		_text[3].init("Spawn Rate:", glm::vec2(700 * _scalingFactors.x, 450 * _scalingFactors.y), _scalingFactors, 1.0f, color, _defaultFont);
		_text[4].init("Resolution:", glm::vec2(220 * _scalingFactors.x, 300 * _scalingFactors.y), _scalingFactors, 1.0f, color, _defaultFont);
		_text[5].init("Screen Mode:", glm::vec2(670 * _scalingFactors.x, 300 * _scalingFactors.y), _scalingFactors, 1.0f, color, _defaultFont);

		//Create sliders for music and sfx volumes
		_sliders.emplace_back();
		_sliders.emplace_back();
		_sliders.emplace_back();
		_sliders.emplace_back();

		//Music Volume
		_sliders[0].init(350.0f * _scalingFactors.x, 600.0f * _scalingFactors.y, 10.0f * _scalingFactors.x, 20.0f * _scalingFactors.y,
						 100.0f * _scalingFactors.x, 7.0f * _scalingFactors.y, 1.0f, _scalingFactors, _options->music * 100, "Textures/slider.png", "Animations/slider.ani",
						 "Textures/line.png", color, callback, _SpriteManager, _defaultFont, _InputManager);
		//SFX Volume
		_sliders[1].init(350.0f * _scalingFactors.x, 450.0f * _scalingFactors.y, 10.0f * _scalingFactors.x, 20.0f * _scalingFactors.y,
						 100.0f * _scalingFactors.x, 7.0f * _scalingFactors.y, 1.0f, _scalingFactors, _options->sfx * 100, "Textures/slider.png", "Animations/slider.ani",
						 "Textures/line.png", color, callback, _SpriteManager, _defaultFont, _InputManager);
		//Spawn Count
		_sliders[2].init(820.0f * _scalingFactors.x, 600.0f * _scalingFactors.y, 10.0f * _scalingFactors.x, 20.0f * _scalingFactors.y,
						 100.0f * _scalingFactors.x, 7.0f * _scalingFactors.y, 1.0f, _scalingFactors, float(_options->spawnCount), "Textures/slider.png", "Animations/slider.ani",
						 "Textures/line.png", color, callback, _SpriteManager, _defaultFont, _InputManager, std::pair<int, int>(100, 1000));
		//_sliders[2].setValue(_options->spawnCount);
		//Spawn Rate
		_sliders[3].init(820.0f * _scalingFactors.x, 450.0f * _scalingFactors.y, 10.0f * _scalingFactors.x, 20.0f * _scalingFactors.y,
						 100.0f * _scalingFactors.x, 7.0f * _scalingFactors.y, 1.0f, _scalingFactors, float(_options->spawnRate), "Textures/slider.png", "Animations/slider.ani",
						 "Textures/line.png", color, callback, _SpriteManager, _defaultFont, _InputManager, std::pair<int, int>(1, 15));
		//_sliders[3].setValue(_options->spawnRate);


		std::function<void(void)> callbackLeft;
		std::function<void(void)> callbackRight;

		_selectionBoxes.emplace_back();
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
		unsigned int max = std::to_string(GameEngine::Screen::validWidths.back()).length() + std::to_string(GameEngine::Screen::validHeights.back()).length() + 1;
		unsigned int curr;
		std::string temp;
		for(unsigned int i = 0; i < GameEngine::Screen::validWidths.size(); i++) {
			oss.clear();
			oss.str("");
			oss << GameEngine::Screen::validWidths[i] << "x" << GameEngine::Screen::validHeights[i];

			//Try to center the string
			oss.seekp(0);
			temp = oss.str();
			curr = temp.length();
			oss.clear();
			oss.str("");
			for(unsigned int k = 0; k < unsigned int((max - curr) * 1.5f); k++) {
				oss << " ";
			}
			oss << temp;
			resolutions.push_back(oss.str());
		}

		_selectionBoxes[0].init(330.0f * _scalingFactors.x, 300.0f * _scalingFactors.y, 25.0f * _scalingFactors.x, 25.0f * _scalingFactors.y, 85.0f * _scalingFactors.x,
								1.0f, _scalingFactors, resolutions, "LEFT", "RIGHT", "Textures/arrows.png", "Animations/arrows.ani", "Textures/arrows.png",
								"Animations/arrows.ani", color, callbackLeft, callbackRight, _SpriteManager, _defaultFont);
		for(unsigned int i = 0; i < GameEngine::Screen::validWidths.size(); i++) {
			if(GameEngine::Screen::validWidths[i] == _options->width) {
				_selectionBoxes[0].setSelection(i);
				break;
			}
		}

		callbackLeft = [&]() {
			_selectionBoxes[1].backward();
		};
		callbackRight = [&]() {
			_selectionBoxes[1].forward();
		};

		std::vector<std::string> modes = std::vector<std::string>{"Borderless Window", "         Windowed", "          Fullscreen"};

		_selectionBoxes[1].init(780.0f * _scalingFactors.x, 300.0f * _scalingFactors.y, 25.0f * _scalingFactors.x, 25.0f * _scalingFactors.y, 150.0f * _scalingFactors.x,
								1.0f, _scalingFactors, modes, "LEFT", "RIGHT", "Textures/arrows.png", "Animations/arrows.ani", "Textures/arrows.png", "Animations/arrows.ani",
								color, callbackLeft, callbackRight, _SpriteManager, _defaultFont);
		if(_options->mode == GameEngine::WindowMode::BORDERLESS) {
			_selectionBoxes[1].setSelection(0);
		} else if(_options->mode == GameEngine::WindowMode::WINDOWED) {
			_selectionBoxes[1].setSelection(1);
		} else if(_options->mode == GameEngine::WindowMode::FULLSCREEN) {
			_selectionBoxes[1].setSelection(2);
		}

		callback = [&]() {
			_options->music = _sliders[0].getValue() / 100.0f;
			_options->sfx = _sliders[1].getValue() / 100.0f;
			_options->spawnCount = unsigned int(round(_sliders[2].getValue()));
			_options->spawnRate = unsigned int(round(_sliders[3].getValue()));
			_options->width = GameEngine::Screen::validWidths[_selectionBoxes[0].getIndex()];
			_options->height = GameEngine::Screen::validHeights[_selectionBoxes[0].getIndex()];
			auto t = _selectionBoxes[1].getIndex();
			if(t == 0) {
				_options->mode = GameEngine::WindowMode::BORDERLESS;
			} else if(t == 1) {
				_options->mode = GameEngine::WindowMode::WINDOWED;
			} else if(t == 2) {
				_options->mode = GameEngine::WindowMode::FULLSCREEN;
			}
			*_gameState = GameState::MAIN_MENU;
		};
		//Create the back button
		_simpleButtons.emplace_back();
		_simpleButtons[0].init(540.0f * _scalingFactors.x, 150.0f * _scalingFactors.y, 200.0f * _scalingFactors.x, 50.0f * _scalingFactors.y, 1.0f,
							   "Textures/buttons.png", "Animations/buttons.ani", "BACK", callback, _SpriteManager);

		//Set the stage state to the game state now that everything is setup
		_stageState = *_gameState;
		break;
	}
	case AWARDS:
	{
		for(unsigned int i = 0; i < 6; i++) {
			for(unsigned int k = 0; k < 17; k++) {
				_SpriteManager->addSprite((2.5f + k * 75.0f) * _scalingFactors.x, (560.0f - i * 85.0f) * _scalingFactors.y, 75.0f * _scalingFactors.x,
										  75.0f * _scalingFactors.y, 1.0f, std::vector<float>{}, "Textures/awardbox.png");
			}
		}

		for(unsigned int i = 0; i < 8; i++) {
			_SpriteManager->addSprite((340.0f + i * 75.0f) * _scalingFactors.x, 50.0f * _scalingFactors.y, 75.0f * _scalingFactors.x, 75.0f * _scalingFactors.y,
									  1.0f, std::vector<float>{}, "Textures/awardbox.png");
		}

		//Make the color blue
		color = GameEngine::COLOR::BLUE;

		_text.emplace_back();
		std::string text = "Awards";

		int x = int(640 - (_titleFont.getFont()->measure(text.c_str()).x / 2));
		int y = int(720 - (_titleFont.getFont()->measure(text.c_str()).y));

		_text[0].init(text, glm::vec2(x * _scalingFactors.x, y * _scalingFactors.y), _scalingFactors, 1.0f, color, &_titleFont);

		callback = [&]() { *_gameState = GameState::MAIN_MENU; };
		//Create the back button
		_simpleButtons.emplace_back();
		_simpleButtons[0].init(1180.0f * _scalingFactors.x, 695.0f * _scalingFactors.y, 100.0f * _scalingFactors.x, 25.0f * _scalingFactors.y, 1.0f,
							   "Textures/buttons.png", "Animations/buttons.ani", "BACK", callback, _SpriteManager);
		_stageState = *_gameState;
		break;
	}
	case REWARDS:
	{
		for(unsigned int i = 0; i < 2; i++) {
			for(unsigned int k = 0; k < 6 - i; k++) {
				_SpriteManager->addSprite((10.0f + k * 170.0f + i * 85.0f) * _scalingFactors.x, (500.0f - i * 170.0f) * _scalingFactors.y, 150.0f * _scalingFactors.x,
										  150.0f * _scalingFactors.y, 1.0f, std::vector<float>{}, "Textures/awardbox.png");
			}
		}
		_SpriteManager->addSprite(945.0f * _scalingFactors.x, 330.0f * _scalingFactors.y, 150.0f * _scalingFactors.x,
								  150.0f * _scalingFactors.y, 1.0f, std::vector<float>{}, "Textures/awardbox.png");

		//Make the color blue
		color = GameEngine::COLOR::BLUE;

		_text.emplace_back();
		_text.emplace_back();
		std::string text = "Rewards";

		int x = int(640 - (_titleFont.getFont()->measure(text.c_str()).x / 2));
		int y = int(720 - (_titleFont.getFont()->measure(text.c_str()).y));

		_text[0].init(text, glm::vec2(x * _scalingFactors.x, y * _scalingFactors.y), _scalingFactors, 1.0f, color, &_titleFont);

		text = "By gaining Awards in Single Nest or Bounty Run Mode, you\nwill earn Reward Keys. Use these Keys in the Rewards Case to\nunlock new tools and abilities to give you the edge in combat.";
		_text[1].init(text, glm::vec2(170.0f * _scalingFactors.x, 225.0f * _scalingFactors.y), _scalingFactors, 1.0f, GameEngine::COLOR::WHITE, &_descriptionFont);

		callback = [&]() { *_gameState = GameState::MAIN_MENU; };
		//Create the back button
		_simpleButtons.emplace_back();
		_simpleButtons[0].init(1180.0f * _scalingFactors.x, 695.0f * _scalingFactors.y, 100.0f * _scalingFactors.x, 25.0f * _scalingFactors.y, 1.0f,
							   "Textures/buttons.png", "Animations/buttons.ani", "BACK", callback, _SpriteManager);
		_stageState = *_gameState;
		break;
	}
	case LOST:
	{
		_simpleButtons.emplace_back();
		callback = [&]() { *_gameState = GameState::MAIN_MENU; };
		_simpleButtons[0].init(540.0f * _scalingFactors.x, 150.0f * _scalingFactors.y, 200.0f * _scalingFactors.x, 50.0f * _scalingFactors.y, 1.0f,
							   "Textures/buttons.png", "Animations/buttons.ani", "BACK", callback, _SpriteManager);

		//Make the color red
		color = GameEngine::COLOR::RED;

		_text.emplace_back();
		std::string text = "You lost.";

		int x = int(640 - (_titleFont.getFont()->measure(text.c_str()).x / 2));
		int y = int(360 - (_titleFont.getFont()->measure(text.c_str()).y / 2));

		_text[0].init(text, glm::vec2(x * _scalingFactors.x, y * _scalingFactors.y), _scalingFactors, 1.0f, color, &_titleFont);

		_stageState = *_gameState;
		break;
	}
	case WON:
	{
		_simpleButtons.emplace_back();
		callback = [&]() { *_gameState = GameState::MAIN_MENU; };
		_simpleButtons[0].init(540.0f * _scalingFactors.x, 150.0f * _scalingFactors.y, 200.0f * _scalingFactors.x, 50.0f * _scalingFactors.y, 1.0f,
							   "Textures/buttons.png", "Animations/buttons.ani", "BACK", callback, _SpriteManager);

		//Make the color blue
		color = GameEngine::COLOR::BLUE;

		_text.emplace_back();
		std::string text = "You won!";

		int x = int(640 - (_titleFont.getFont()->measure(text.c_str()).x / 2));
		int y = int(360 - (_titleFont.getFont()->measure(text.c_str()).y / 2));

		_text[0].init(text, glm::vec2(x * _scalingFactors.x, y * _scalingFactors.y), _scalingFactors, 1.0f, color, &_titleFont);

		_stageState = *_gameState;
	}
	case EXIT: break;
	default: break;
	}
}