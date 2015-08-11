#pragma once
#include <GL/glew.h>
#include <SDL/SDL.h>

#include <GameEngine/Window.h>

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
	void close();

private:
	GameEngine::Window _window;
	GameState _gameState;
};

