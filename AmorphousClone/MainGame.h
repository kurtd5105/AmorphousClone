#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>
#include <GL/glew.h>
#include <SDL/SDL.h>

#include <GameEngine/Camera.h>
#include <GameEngine/FontBatcher.h>
#include <GameEngine/FPSManager.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/IOManager.h>
#include <GameEngine/ResourceManager.h>
#include <GameEngine/ShadingProgram.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteBatcher.h>
#include <GameEngine/SpriteManager.h>
#include <GameEngine/Text.h>
#include <GameEngine/ThreadState.h>
#include <GameEngine/Window.h>

#include "StagingManager.h"
#include "GameState.h"
#include "GameLogic.h"
#include "SpawnManager.h"


class MainGame {
public:
	MainGame();
	~MainGame();

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	//Vectors containing all the required textures
	std::vector<std::string> TEXTURE_LIST_SYNC = std::vector<std::string>{"Textures/buttons.png", "Textures/loading.png", "Textures/checkbox.png"};
	std::vector<std::string> TEXTURE_LIST_ASYNC = std::vector<std::string>{"Textures/player.png", "Textures/tile1.png", "Textures/example_enemy.png", "Textures/sword.png"};
	std::vector<std::string> ANIMATION_LIST_SYNC = std::vector<std::string>{"Animations/buttons.ani", "Animations/checkbox.ani"};

	std::vector<std::string> SHADING_ATTRIBUTES = std::vector<std::string>{"vertexPosition", "vertexColor", "vertexUV"};

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

	StagingManager _StagingManager;
	GameLogic _Game;
	GameState _gameState;
	//SpawnManager _SpawnManager;

	std::thread _IOThread;
	ThreadState _IOThreadState;
};
