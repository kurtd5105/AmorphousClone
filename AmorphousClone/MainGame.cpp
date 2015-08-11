#include "MainGame.h"


MainGame::MainGame() : _gameState(MAIN_MENU) {
}


MainGame::~MainGame() {
}

void MainGame::startGame() {
	init();
	gameLoop();
	close();
}

void MainGame::init() {
	_window.createWindow(800, 600, "Amorphous Clone", GameEngine::WindowMode::WINDOWED);
}

void MainGame::gameLoop() {
	while(_gameState != GameState::EXIT) {
		processInput();
	}
}

void MainGame::processInput() {
	SDL_Event event;

	//Get the pointer to the state of the keyboard key presses
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	//Poll every event and handle it
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		//If the user clicked the close button
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		}
	}

	//Handle keyboard input here
}

void MainGame::close() {
	_window.destroySDLWindow();
	SDL_Quit();
}