#pragma once
#include <GL/glew.h>
#include <SDL/SDL.h>

#include <GameEngine/Window.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/IOManager.h>

enum GameState {
	MAIN_MENU, PLAYING, EXIT
};

class MainGame {
public:
	MainGame();
	~MainGame();

	void startGame();
	void init();
	
	void gameLoop();

	void processInput();
	void renderGame();

	void close();

private:
	GameEngine::Window _window;
	GameEngine::InputManager _inputManager;
	GameEngine::IOManager _IOManager;
	GameState _gameState;
};

