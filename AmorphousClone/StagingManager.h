#pragma once
#include <functional>
#include <list>

#include <GameEngine/Button.h>
#include <GameEngine/SimpleButton.h>

#include <GameEngine/SpriteManager.h>
#include <GameEngine/FontBatcher.h>
#include <GameEngine/Text.h>

#include "GameState.h"
#include "Player.h"
#include "SpawnManager.h"

class StagingManager {
public:
	StagingManager();
	~StagingManager();

	void init(GameState* gameState, GameEngine::SpriteManager* manager, GameEngine::FontBatcher* defaultFont);
	void loadState();

	GameState getStageState() { return _stageState; }
	std::vector<GameEngine::SimpleButton>* getSimpleButtonRefs() { return &_simpleButtons; }
	std::vector<GameEngine::FontBatcher>* getFonts() { return &_fonts; }
	SpawnManager* getSpawnManager() { return &_SpawnManager; }

	Player* getPlayer() { return &_player; }

private:
	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::FontBatcher* _defaultFont;

	std::vector<GameEngine::SimpleButton> _simpleButtons;
	std::vector<GameEngine::Text> _text;
	std::vector<GameEngine::FontBatcher> _fonts;

	Player _player;

	SpawnManager _SpawnManager;

	GameState* _gameState;
	GameState _stageState;
};

