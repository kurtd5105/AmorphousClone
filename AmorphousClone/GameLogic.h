#pragma once
#include <vector>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <GameEngine/InputManager.h>
#include <GameEngine/Camera.h>
#include <GameEngine/CollisionManager.h>

#include "GameState.h"
#include "StagingManager.h"
#include "Button.h"

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

