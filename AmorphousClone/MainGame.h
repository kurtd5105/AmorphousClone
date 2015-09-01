#pragma once
#include <GL/glew.h>
#include <SDL/SDL.h>

#include <iostream>

#include <thread>

#include <GameEngine/Window.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/IOManager.h>
#include <GameEngine/ResourceManager.h>
#include <GameEngine/ShadingProgram.h>
#include <GameEngine/SpriteManager.h>
#include <GameEngine/SpriteBatcher.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/Camera.h>
#include <GameEngine/FPSManager.h>

#include <GameEngine/ThreadState.h>

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
	std::vector<std::string> TEXTURE_LIST_SYNC = std::vector<std::string>{"Textures/buttons.png", "Textures/loading.png"};
	std::vector<std::string> TEXTURE_LIST_ASYNC = std::vector<std::string>{"Textures/player.png", "Textures/tile1.png"};

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

	GameEngine::Camera _Camera;

	GameEngine::FPSManager _FPSManager;

	StagingManager _StagingManager;
	GameLogic _Game;//more important than fps manager thx github
	GameState _gameState;

	std::thread _IOThread;
	ThreadState _IOThreadState;
};

