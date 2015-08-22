#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include <GameEngine/InputManager.h>
#include <GameEngine/Camera.h>

#include "GameState.h"

class GameLogic {
public:
	GameLogic();
	~GameLogic();

	void init(GameState* gameState, GameEngine::Camera* camera);
	void processInput();
private:
	GameEngine::InputManager _InputManager;
	GameEngine::Camera* _Camera;

	GameState* _gameState;
};

