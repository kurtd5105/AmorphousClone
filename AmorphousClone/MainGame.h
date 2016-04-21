#pragma once

#include <iostream>
#include <thread>

#include <GameEngine/Camera.h>
#include <GameEngine/FontBatcher.h>
#include <GameEngine/FPSManager.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/IOManager.h>
#include <GameEngine/Options.h>
#include <GameEngine/ResourceManager.h>
#include <GameEngine/ShadingProgram.h>
#include <GameEngine/SpriteBatcher.h>
#include <GameEngine/SpriteManager.h>
#include <GameEngine/ThreadState.h>
#include <GameEngine/Window.h>

#include "StagingManager.h"
#include "GameState.h"
#include "GameLogic.h"


class MainGame {
public:
	MainGame();
	~MainGame();

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	//Vectors containing all the required textures
	const std::vector<std::string> TEXTURE_LIST_SYNC = std::vector<std::string>{"Textures/buttons.png", "Textures/loading.png", "Textures/checkbox.png",
		"Textures/slider.png", "Textures/line.png", "Textures/arrows.png", "Textures/lock.png", "Textures/lockfancy.png"};
	const std::vector<std::string> TEXTURE_LIST_ASYNC = std::vector<std::string>{"Textures/player.png", "Textures/tile1.png", "Textures/example_enemy.png",
		"Textures/sword.png", "Textures/gravel.png", "Textures/stickie.png", "Textures/playerSticky.png"};
	const std::vector<std::string> ANIMATION_LIST_SYNC = std::vector<std::string>{"Animations/buttons.ani", "Animations/checkbox.ani", "Animations/slider.ani",
		"Animations/arrows.ani"};

	const std::vector<std::string> SHADING_ATTRIBUTES = std::vector<std::string>{"vertexPosition", "vertexColor", "vertexUV"};

	void startGame();
	void init();

	void gameLoop();

	void renderGame();

	void close();

private:
	GameEngine::Window _Window;

	GameEngine::InputManager _InputManager;

	GameEngine::IOManager _IOManager;
	GameEngine::ResourceManager _ResourceManager = GameEngine::ResourceManager(&_IOManager);

	GameEngine::ShadingProgram _ShadingProgram;
	GameEngine::SpriteManager _SpriteManager;
	GameEngine::SpriteBatcher _SpriteBatcher;

	GameEngine::FontBatcher _fontBatcher_sans16;

	GameEngine::Camera _Camera;

	GameEngine::FPSManager _FPSManager;

	GameEngine::Options* _options;

	StagingManager _StagingManager;
	GameLogic _Game;
	GameState _gameState;
	//SpawnManager _SpawnManager;

	std::thread _IOThread;
	ThreadState _IOThreadState;

	glm::vec2 _scalingFactors;
};
