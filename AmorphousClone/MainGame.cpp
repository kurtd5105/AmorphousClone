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
	//Test textures with a large file size for extending async load time
	//_ResourceManager.asyncLoadTexture(std::vector<std::string>{"Textures/01.png", "Textures/02.png", "Textures/03.png"}, _IOThread, &_IOThreadState);
	_ResourceManager.asyncLoadTexture(TEXTURE_LIST_ASYNC, _IOThread, &_IOThreadState);

	//Init classes
	_SpriteManager.init(GameEngine::sortType::TEXTURE, &_ResourceManager);
	_StagingManager.init(&_gameState, &_SpriteManager);
	_Camera.init(WINDOW_WIDTH, WINDOW_HEIGHT);
	_Game.init(&_gameState, &_Camera, &_StagingManager);
	_SpriteBatcher.init();

	//_SpriteBatcher.setNewBatch(_SpriteManager.getSprites());

	_FPSManager.fpsinit();
}

void MainGame::gameLoop() {
	GameState currState = _gameState;
	Uint32 prevTick = SDL_GetTicks();
	float prevFPS = _FPSManager.framespersecond;

	while(_gameState != GameState::EXIT) {
		//Handle thread state switching
		if(_IOThreadState == ThreadState::FINISHED) {
			std::cout << ">> Async loading complete. Thread closed." << std::endl;
			_IOThreadState = ThreadState::POST_LOAD;
		}

		//If the game is loading then a post load can occur
		if(_gameState == GameState::LOADING && _IOThreadState == ThreadState::POST_LOAD) {
			for(auto& path : TEXTURE_LIST_ASYNC) {
				_ResourceManager.getTexture(path);
			}
			_IOThreadState = ThreadState::OFF;
		}

		//Handle state switching with threading
		//
		//Thread is off and switch request can switch instantly
		if(currState != _gameState && _IOThreadState == ThreadState::OFF) {
			_StagingManager.loadState();
			currState = _gameState;
		//Thread is on or post load and switch request requires switch to loading where thread will complete and post load will occur
		//Game will be in loading state while thread completes loading and post load
		} else if(currState != _gameState && (_IOThreadState == ThreadState::ON || _IOThreadState == ThreadState::POST_LOAD)) {
			std::cout << "Waiting on thread to complete or post load." << std::endl;
			_gameState = GameState::LOADING;
			currState = _gameState;
			_StagingManager.loadState();
			_Game.getStage();
		//Thread is complete and game state is loading, switch can now occur
		} else if(_gameState == GameState::LOADING && _IOThreadState == ThreadState::OFF) {
			_gameState = GameState::PLAYING;
			currState = _gameState;
			_StagingManager.loadState();
			_Game.getStage();
		}

		//Process the game input
		_Game.processInput();

		//Optional to update the batch, could be moved to automatically update every batch creation
		//_SpriteBatcher.setNewBatch(_SpriteManager.getSprites());

		_FPSManager.fpsthink();
		if((SDL_GetTicks() - prevTick) > _FPSManager.framespersecond/2) {
			std::cout << "FPS: " << _FPSManager.framespersecond << std::endl;
			prevTick = SDL_GetTicks();
		}
		
		renderGame();
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
	_SpriteBatcher.setupBatches(_SpriteManager.getSprites());
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