#pragma once
#include <vector>
#include <list>

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <glm/glm.hpp>

#include <GameEngine/Camera.h>
#include <GameEngine/CollisionManager.h>
#include <GameEngine/InputManager.h>

#include "Button.h"
#include "GameState.h"
#include "Player.h"
#include "EnemySuper.h"
#include "StagingManager.h"
#include "SpawnManager.h"

class GameLogic {
public:
	GameLogic();
	~GameLogic();

	void init(GameState* gameState, GameEngine::Camera* camera, StagingManager* manager);

	void updateEnemy();
	void processInput();
	void getStage();

private:
	GameEngine::InputManager _InputManager;
	GameEngine::Camera* _Camera;
	StagingManager* _StagingManager;
	SpawnManager* _SpawnManager;

	GameState* _gameState;

	std::vector<bool>* _keys;

	std::vector<Button>* _buttonRefs;
	Player* _player;
	std::list<EnemySuper>* _enemies;

	int W, A, S, D, Q, E;
};

