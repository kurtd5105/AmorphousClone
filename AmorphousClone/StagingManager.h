#pragma once
#include <GameEngine/SpriteManager.h>

#include "GameState.h"
#include "Button.h"


class StagingManager {
public:
	StagingManager();
	~StagingManager();

	void init(GameState* gameState, GameEngine::SpriteManager* manager);
	void loadState();

	std::vector<Button>* getButtonRefs() { return &_buttons; }

private:
	GameEngine::SpriteManager* _SpriteManager;

	std::vector<Button> _buttons;

	GameState* _gameState;
};

