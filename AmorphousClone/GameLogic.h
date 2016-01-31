#pragma once
#include <vector>
#include <list>

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <glm/glm.hpp>

#include <GameEngine/Button.h>
#include <GameEngine/Camera.h>
#include <GameEngine/CollisionManager.h>
#include <GameEngine/InputManager.h>

#include "GameState.h"
#include "Player.h"
#include "EnemySuper.h"
#include "StagingManager.h"
#include "SpawnManager.h"

class GameLogic {
public:
	GameLogic();
	~GameLogic();

	void init(GameState* gameState, GameEngine::Camera* camera, StagingManager* manager, GameEngine::InputManager* inputManager);

	void updateEnemy(float step);
	void processInput(float step);
	void checkButtons(glm::vec2& mouseCoords);
	void getStage();
	void collisionAgents();

private:
	GameEngine::InputManager* _InputManager;
	GameEngine::Camera* _Camera;
	StagingManager* _StagingManager;
	SpawnManager* _SpawnManager;

	GameState* _gameState;

	std::vector<bool>* _keys;

	std::vector<GameEngine::SimpleButton>* _simpleButtonRefs;
	std::vector<GameEngine::Checkbox>* _checkboxRefs;
	std::vector<GameEngine::Slider>* _sliderRefs;
	GameEngine::Button* _currClicked;
	Player* _player;
	std::list<EnemySuper>* _enemies;

	int W, A, S, D, Q, E;
	bool _clickHold;
};

