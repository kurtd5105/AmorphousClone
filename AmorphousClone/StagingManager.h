#pragma once
#include <list>

#include <GameEngine/SpriteManager.h>

#include "Button.h"
#include "GameState.h"
#include "Player.h"
#include "SpawnManager.h"

class StagingManager {
public:
	StagingManager();
	~StagingManager();

	void init(GameState* gameState, GameEngine::SpriteManager* manager);
	void loadState();

	std::vector<Button>* getButtonRefs() { return &_buttons; }
	SpawnManager* getSpawnManager() { return &_SpawnManager; }

	Player* getPlayer() { return &_player; }

private:
	GameEngine::SpriteManager* _SpriteManager;

	std::vector<Button> _buttons;

	Player _player;

	SpawnManager _SpawnManager;

	GameState* _gameState;
};

