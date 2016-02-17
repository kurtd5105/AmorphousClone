#pragma once

#include <GameEngine/Checkbox.h>
#include <GameEngine/SimpleButton.h>
#include <GameEngine/Slider.h>
#include <GameEngine/SelectionBox.h>

#include <GameEngine/FontBatcher.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/Options.h>
#include <GameEngine/SpriteManager.h>
#include <GameEngine/Text.h>

#include "GameState.h"
#include "Player.h"
#include "SpawnManager.h"

class StagingManager {
public:
	StagingManager();
	~StagingManager();

	void init(GameState* gameState, GameEngine::Options* options, GameEngine::SpriteManager* manager, GameEngine::FontBatcher* defaultFont, GameEngine::InputManager* inputManager);
	void loadState();

	GameState getStageState() const { return _stageState; }

	std::vector<GameEngine::SimpleButton>* getSimpleButtonRefs() { return &_simpleButtons; }
	std::vector<GameEngine::Checkbox>* getCheckboxRefs() { return &_checkboxes; }
	std::vector<GameEngine::Slider>* getSliderRefs() { return &_sliders; }
	std::vector<GameEngine::SelectionBox>* getSelectionRefs() { return &_selectionBoxes; }

	std::vector<GameEngine::FontBatcher>* getFonts() { return &_fonts; }
	SpawnManager* getSpawnManager() { return &_SpawnManager; }

	Player* getPlayer() { return &_player; }

	const std::vector<int> validWidths = std::vector<int>{800, 1024, 1280, 1360, 1366, 1440, 1600, 1980};
	const std::vector<int> validHeights = std::vector<int>{600, 768, 720, 768, 768, 900, 900, 1080};

private:
	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::InputManager* _InputManager;
	GameEngine::FontBatcher* _defaultFont;
	GameEngine::Options* _options;

	//Refactor later so they are all in one vector
	std::vector<GameEngine::SimpleButton> _simpleButtons;
	std::vector<GameEngine::Checkbox> _checkboxes;
	std::vector<GameEngine::Slider> _sliders;
	std::vector<GameEngine::SelectionBox> _selectionBoxes;

	std::vector<GameEngine::Text> _text;
	std::vector<GameEngine::FontBatcher> _fonts;

	Player _player;

	SpawnManager _SpawnManager;

	GameState* _gameState;
	GameState _stageState;
};

