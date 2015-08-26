#pragma once
#include <GameEngine/SpriteManager.h>

#include "Button.h"
#include "GameState.h"
#include "Player.h"



class StagingManager {
public:
	StagingManager();
	~StagingManager();

	void init(GameState* gameState, GameEngine::SpriteManager* manager);
	void loadState();

	std::vector<Button>* getButtonRefs() { return &_buttons; }
	Player* getPlayer() { return &_player; }

private:
	GameEngine::SpriteManager* _SpriteManager;

	std::vector<Button> _buttons;
	Player _player;

	GameState* _gameState;
};

