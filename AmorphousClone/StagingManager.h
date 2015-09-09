#pragma once
#include <list>

#include <GameEngine/SpriteManager.h>

#include "Button.h"
#include "GameState.h"
#include "Player.h"
#include "Goople.h"


class StagingManager {
public:
	StagingManager();
	~StagingManager();

	void init(GameState* gameState, GameEngine::SpriteManager* manager);
	void loadState();

	std::vector<Button>* getButtonRefs() { return &_buttons; }

	Player* getPlayer() { return &_player; }
	std::list<Goople>* getGooples() { return &_gooples; }

private:
	GameEngine::SpriteManager* _SpriteManager;

	std::vector<Button> _buttons;

	Player _player;
	std::list<Goople> _gooples;

	GameState* _gameState;
};

