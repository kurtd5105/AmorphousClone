#pragma once
#include <vector>
#include <list>

#include <glm/glm.hpp>

#include <GameEngine/Button.h>
#include <GameEngine/Checkbox.h>
#include <GameEngine/SimpleButton.h>
#include <GameEngine/Slider.h>
#include <GameEngine/SelectionBox.h>

#include <GameEngine/Camera.h>
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

	void updateEnemy(float step) const;
	void processInput(float step);
	void checkButtons(glm::vec2& mouseCoords);
	void getStage();
	void collisionAgents() const;

	const std::vector<int> validWidths = std::vector<int>{800, 1024, 1280, 1360, 1366, 1440, 1600, 1980};
	const std::vector<int> validHeights = std::vector<int>{600, 768, 720, 768, 768, 900, 900, 1080};

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
	std::vector<GameEngine::SelectionBox>* _selectionRefs;

	GameEngine::Button* _currClicked;
	Player* _player;
	std::list<EnemySuper>* _enemies;
	glm::vec2 _tempTarget;

	int W, A, S, D, Q, E;
	bool _clickHold;
};

