#include "MainGame.h"
#include <iostream>

MainGame::MainGame() : _gameState(MAIN_MENU), _IOThreadState(ThreadState::OFF) {
}


MainGame::~MainGame() {
}

void MainGame::startGame() {
	init();
	gameLoop();
	close();
}

void MainGame::init() {
	_Window.createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Amorphous Clone", GameEngine::WindowMode::WINDOWED);

	//Load textures into memory, either they are loaded at the start of the game or not and we track
	//the status of the rest of the textures

	for(auto& filePath : TEXTURE_LIST_SYNC) {
		_ResourceManager.syncLoadTexture(filePath);
	}

	_ShadingProgram.init("Shaders/shader.vert", "Shaders/shader.frag", SHADING_ATTRIBUTES, &_IOManager);
	//_ResourceManager.asyncLoadTexture(std::vector<std::string>{"Textures/01.png", "Textures/02.png", "Textures/03.png"}, _IOThread, &_IOThreadState);
	//_ResourceManager.asyncLoadTexture(TEXTURE_LIST_ASYNC, _IOThread, &_IOThreadState);

	//Init classes
	_SpriteManager.init(GameEngine::sortType::TEXTURE, &_ResourceManager);
	_StagingManager.init(&_gameState, &_SpriteManager);
	_Camera.init(WINDOW_WIDTH, WINDOW_HEIGHT);
	_Game.init(&_gameState, &_Camera, &_StagingManager);
	_SpriteBatcher.init();

	_SpriteBatcher.setNewBatch(_SpriteManager.getSprites());
}

void MainGame::gameLoop() {
	while(_gameState != GameState::EXIT) {
		_Game.processInput();
		//processInput();
		//std::cout << "State: " << (_gameState == GameState::PLAYING ? "playing." : _gameState == GameState::MAIN_MENU ? "main menu." : "exit.") << std::endl;

		//Optional to update the batch, could be moved to automatically update every batch creation
		_SpriteBatcher.setNewBatch(_SpriteManager.getSprites());
		renderGame();
		if(_IOThreadState == ThreadState::FINISHED) {
			//_SpriteManager.addSprite(100.0f, 300.0f, 500.0f, 500.0f, 1.0f, "Textures/03.png");
			//_SpriteManager.addSprite(200.0f, 100.0f, 500.0f, 500.0f, 1.0f, "Textures/03.png");

			//_SpriteBatcher.setNewBatch(_SpriteManager.getSprites());
			_IOThreadState = ThreadState::OFF;
		}
	}
}

void MainGame::renderGame() {
	_Camera.update();
	//Clear the screen
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Start using the shading program
	_ShadingProgram.use();

	glActiveTexture(GL_TEXTURE0);

	//Get the texture uniform
	GLint textureLocation = _ShadingProgram.getUniformLocation("playerTexture");
	glUniform1i(textureLocation, 0);

	//Get the position uniform
	GLint positionLocation = _ShadingProgram.getUniformLocation("P");

	float *cameraMatrix = _Camera.getMatrixRef();
	glUniformMatrix4fv(positionLocation, 1, GL_FALSE, cameraMatrix);

	_SpriteBatcher.cleanUp();
	_SpriteBatcher.setupBatches();
	_SpriteBatcher.renderBatch();

	_ShadingProgram.unuse();

	glBindTexture(GL_TEXTURE_2D, 0);

	_Window.swapBuffer();
}

void MainGame::close() {
	if(_IOThread.joinable()) {
		_IOThread.join();
	} else {
		_IOThread.~thread();
	}

	_Window.destroySDLWindow();
	SDL_Quit();
	//int a;
	//std::cout << "Enter a key to close. ";
	//std::cin >> a;
}