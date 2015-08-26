#pragma once
#include <vector>

#include <GL/glew.h>
#include <SDL/SDL.h>

#include <GameEngine/Camera.h>
#include <GameEngine/CollisionManager.h>
#include <GameEngine/InputManager.h>

#include "Button.h"
#include "GameState.h"
#include "Player.h"
#include "StagingManager.h"


class GameLogic {
public:
	GameLogic();
	~GameLogic();

	void init(GameState* gameState, GameEngine::Camera* camera, StagingManager* manager);
	void processInput();
private:
	GameEngine::InputManager _InputManager;
	GameEngine::Camera* _Camera;
	StagingManager* _StagingManager;

	GameState* _gameState;

	std::vector<bool>* _keys;

	int W, A, S, D, Q, E;
};

