#pragma once
#include "GameState.h"
#include <GameEngine/SpriteManager.h>

class StagingManager {
public:
	StagingManager();
	~StagingManager();

	void init(GameState* gameState, GameEngine::SpriteManager* manager);
	void loadState();

private:
	GameEngine::SpriteManager* _SpriteManager;

	GameState* _gameState;
};

