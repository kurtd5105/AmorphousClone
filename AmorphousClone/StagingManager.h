#pragma once

#include <GameEngine/Checkbox.h>
#include <GameEngine/SimpleButton.h>
#include <GameEngine/Slider.h>
#include <GameEngine/SelectionBox.h>

#include <GameEngine/FontBatcher.h>
#include <GameEngine/Text.h>

#include "GameState.h"

namespace GameEngine {
	class InputManager;
	struct Options;
	class ResourceManager;
	class SpriteManager;
}

class Player;
class SpawnManager;

class StagingManager {
public:
	StagingManager();
	~StagingManager();

	void init(GameState* gameState, GameEngine::Options* options, glm::vec2 scalingFactors, GameEngine::ResourceManager* resourceManager,
			  GameEngine::SpriteManager* spriteManager, GameEngine::FontBatcher* defaultFont, GameEngine::InputManager* inputManager);
	void loadState();

	GameState getStageState() const { return _stageState; }

	GameEngine::Options* getOptions() const { return _options; }

	std::vector<GameEngine::SimpleButton>* getSimpleButtonRefs() { return &_simpleButtons; }
	std::vector<GameEngine::Checkbox>* getCheckboxRefs() { return &_checkboxes; }
	std::vector<GameEngine::Slider>* getSliderRefs() { return &_sliders; }
	std::vector<GameEngine::SelectionBox>* getSelectionRefs() { return &_selectionBoxes; }
	std::vector<GameEngine::Text>* getText() { return &_text; };
	std::vector<GameEngine::FontBatcher*>* getFonts() { return &_fonts; }
	SpawnManager* getSpawnManager() const { return _SpawnManager; }

	Player* getPlayer() const { return _player; }

	
private:
	GameEngine::ResourceManager* _ResourceManager;
	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::InputManager* _InputManager;
	GameEngine::FontBatcher* _defaultFont;
	GameEngine::FontBatcher _titleFont;
	GameEngine::FontBatcher _descriptionFont;
	GameEngine::Options* _options;

	//Refactor later so they are all in one vector
	std::vector<GameEngine::SimpleButton> _simpleButtons;
	std::vector<GameEngine::Checkbox> _checkboxes;
	std::vector<GameEngine::Slider> _sliders;
	std::vector<GameEngine::SelectionBox> _selectionBoxes;

	std::vector<GameEngine::Text> _text;
	std::vector<GameEngine::FontBatcher*> _fonts;

	Player* _player;

	SpawnManager* _SpawnManager;

	GameState* _gameState;
	GameState _stageState;

	glm::vec2 _scalingFactors;
};

