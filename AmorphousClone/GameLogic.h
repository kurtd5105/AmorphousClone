#pragma once
#include <vector>
#include <list>
#include <deque>
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

// Contains all the game logic to be processed on each frame.
class GameLogic {
public:
	GameLogic();
	~GameLogic();

	void init(GameState* gameState, GameEngine::Camera* camera, StagingManager* manager, GameEngine::InputManager* inputManager);

	// TODO: Make private.
	// Moves the enemies towards their targets.
	void updateEnemy(float step);

	// Processes the input and moves the player.
	void processInput(float step);

	// TODO: Make private.
	// Checks buttons for mouse events.
	void checkButtons(glm::vec2& mouseCoords);

	// TODO: Make private.
	// Gets the stage state and the required vectors of game objects.
	void getStage();

	// TODO: Make private.
	// TODO: Move score out of this function into a new one.
	// Runs collisions on the agents and counts score.
	void collisionAgents();

private:
	// Increments the correct counter based on enemy type.
	static void countEnemy(EnemySuper* enemy, int& goopleCount, int& stickieCount);

	GameEngine::InputManager* _InputManager;
	GameEngine::Camera* _Camera;
	StagingManager* _StagingManager;
	SpawnManager* _SpawnManager;

	GameState* _gameState;
	GameState _curr;

	std::vector<bool>* _keys;

	std::vector<GameEngine::SimpleButton>* _simpleButtonRefs;
	std::vector<GameEngine::Checkbox>* _checkboxRefs;
	std::vector<GameEngine::Slider>* _sliderRefs;
	std::vector<GameEngine::SelectionBox>* _selectionRefs;
	std::vector<GameEngine::Text>* _textRefs;
	std::deque<StickieGoo*> _goos;

	GameEngine::Button* _currClicked;
	Player* _player;
	std::list<EnemySuper>* _enemies;

	int W, A, S, D, Q, E;
	int _gloopleKills, _biterKills, _meltieKills, _stickieKills, _totalKills, _score;
	int _gloopleSwing, _biterSwing, _meltieSwing, _stickieSwing;
	bool _clickHold;
};

