#pragma once
#include <functional>
#include <list>

#include <GameEngine/Button.h>
#include <GameEngine/Checkbox.h>
#include <GameEngine/SimpleButton.h>
#include <GameEngine/Slider.h>

#include <GameEngine/FontBatcher.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/Options.h>
#include <GameEngine/SpriteManager.h>
#include <GameEngine/Text.h>
#include <GameEngine/Vertex.h>

#include "GameState.h"
#include "Player.h"
#include "SpawnManager.h"

class StagingManager {
public:
	StagingManager();
	~StagingManager();

	void init(GameState* gameState, GameEngine::Options* options, GameEngine::SpriteManager* manager, GameEngine::FontBatcher* defaultFont, GameEngine::InputManager* inputManager);
	void loadState();

	GameState getStageState() { return _stageState; }
	std::vector<GameEngine::SimpleButton>* getSimpleButtonRefs() { return &_simpleButtons; }
	std::vector<GameEngine::Checkbox>* getCheckboxRefs() { return &_checkboxes; }
	std::vector<GameEngine::Slider>* getSliderRefs() { return &_sliders; }
	std::vector<GameEngine::FontBatcher>* getFonts() { return &_fonts; }
	SpawnManager* getSpawnManager() { return &_SpawnManager; }

	Player* getPlayer() { return &_player; }

private:
	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::InputManager* _InputManager;
	GameEngine::FontBatcher* _defaultFont;
	GameEngine::Options* _options;

	//Refactor later so they are all in one vector
	std::vector<GameEngine::SimpleButton> _simpleButtons;
	std::vector<GameEngine::Checkbox> _checkboxes;
	std::vector<GameEngine::Slider> _sliders;

	std::vector<GameEngine::Text> _text;
	std::vector<GameEngine::FontBatcher> _fonts;

	Player _player;

	SpawnManager _SpawnManager;

	GameState* _gameState;
	GameState _stageState;
};

