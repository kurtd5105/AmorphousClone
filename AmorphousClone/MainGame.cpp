#include "MainGame.h"
#include <iostream>

MainGame::MainGame() : _options(nullptr), _gameState(MAIN_MENU), _IOThreadState(ThreadState::OFF) {}


MainGame::~MainGame() {
	delete _options;
}

void MainGame::startGame() {
	init();
	gameLoop();
	close();
}

void MainGame::init() {
	_options = new GameEngine::Options;
	_IOManager.loadOptions(_options);
	_Window.createWindow(_options, "Amorphous Clone");

	//Load textures into memory, either they are loaded at the start of the game or not and we track
	//the status of the rest of the textures

	for (auto& filePath : TEXTURE_LIST_SYNC) {
		_ResourceManager.syncLoadTexture(filePath);
	}
	for(auto& filePath : ANIMATION_LIST_SYNC) {
		_ResourceManager.syncLoadAnimation(filePath);
	}

	_ShadingProgram.init("Shaders/shader.vert", "Shaders/shader.frag", SHADING_ATTRIBUTES, &_IOManager);
	//Test textures with a large file size for extending async load time
	//_ResourceManager.asyncLoadTexture(std::vector<std::string>{"Textures/01.png", "Textures/02.png", "Textures/03.png"}, _IOThread, &_IOThreadState);
	_ResourceManager.asyncAssetLoad(TEXTURE_LIST_ASYNC, std::vector<std::string>{}, _IOThread, &_IOThreadState);

	//Init classes
	_SpriteManager.init(GameEngine::sortType::TEXTURE, &_ResourceManager);

	//TTF init
	_fontBatcher_sans16.init("Fonts/OpenSans-Regular.ttf", 16, &_ResourceManager);

	//_SpawnManager.init(WINDOW_WIDTH, WINDOW_HEIGHT, 20, &_SpriteManager);
	_StagingManager.init(&_gameState, _options, &_SpriteManager, &_fontBatcher_sans16, &_InputManager);
	_Camera.init(WINDOW_WIDTH, WINDOW_HEIGHT);
	_Game.init(&_gameState, &_Camera, &_StagingManager, &_InputManager);
	_SpriteBatcher.init();

	//_SpriteBatcher.setNewBatch(_SpriteManager.getSprites());

	_FPSManager.fpsinit();
}

void MainGame::gameLoop() {
	auto currState = _gameState;
	auto desiredState = _gameState;

	auto currFPSTick = SDL_GetTicks();
	auto prevFPSTick = currFPSTick;
	//auto prevFPS = _FPSManager.framespersecond;

	auto prevTick = std::chrono::system_clock::now().time_since_epoch().count();
	auto currTick = prevTick;
	auto frameTime = currTick - prevTick;
	std::chrono::system_clock::rep accumulator = 0;
	std::chrono::system_clock::rep maxTime = 60000000 / 60;
	std::chrono::system_clock::rep dt = 10000000 / 60;

	while (_gameState != GameState::EXIT) {
		//Handle thread state switching
		if (_IOThreadState == ThreadState::FINISHED) {
			std::cout << ">> Async loading complete. Thread closed." << std::endl;
			_IOThreadState = ThreadState::POST_LOAD;
		}

		//If the game is loading then a post load can occur
		if (_gameState == GameState::LOADING && _IOThreadState == ThreadState::POST_LOAD) {
			for (auto& path : TEXTURE_LIST_ASYNC) {
				_ResourceManager.getTexture(path);
			}
			_IOThreadState = ThreadState::OFF;
		}

		//Handle state switching with threading
		//
		//Thread is off and switch request can switch instantly
		if (currState != _gameState && _IOThreadState == ThreadState::OFF) {
			_StagingManager.loadState();
			currState = _gameState;
			//Thread is on or post load and switch request requires switch to loading where thread will complete and post load will occur
			//Game will be in loading state while thread completes loading and post load
		}
		else if (currState != _gameState && (_IOThreadState == ThreadState::ON || _IOThreadState == ThreadState::POST_LOAD)) {
			std::cout << "Waiting on thread to complete or post load." << std::endl;
			desiredState = _gameState;
			_gameState = GameState::LOADING;
			currState = _gameState;
			accumulator = 0;
			_StagingManager.loadState();
			_Game.getStage();
			//Thread is complete and game state is loading, switch can now occur
		}
		else if (_gameState == GameState::LOADING && _IOThreadState == ThreadState::OFF) {
			_gameState = desiredState;
			currState = _gameState;
			accumulator = 0;
			_StagingManager.loadState();
			_Game.getStage();
		}

		_FPSManager.fpsthink();

		//Set up the ticks to count the frame time
		//Possible to use the FPS manager in the future?
		prevTick = currTick;
		currTick = std::chrono::system_clock::now().time_since_epoch().count();
		currFPSTick = SDL_GetTicks();
		frameTime = currTick - prevTick;

		//Cap the speed of the game at 10 FPS min, then slow the game down
		if(frameTime > maxTime) {
			std::cout << "FPS is low, frame time exceeded max allowed frame time: " << frameTime << std::endl;
			frameTime = maxTime;
		}
		accumulator += frameTime;

		//Process steps of 1 frame
		while(accumulator >= dt) {
			_Game.processInput(1.0f);
			accumulator -= dt;
		}

		//Or game could be updated for every frame, but there will be more slowdown effect if frame times are inconsistent
		//_Game.processInput(frameTime/(1000.0f/60.0f));

		//Process input no matter what
		_Game.processInput(0.0f);
		
		//Print out the FPS and the accumulator every 2 seconds
		if (currFPSTick - prevFPSTick > 2000) {
			std::cout << "FPS: " << _FPSManager.framespersecond << ", " << accumulator << std::endl;
			//std::cout << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
			prevFPSTick = currFPSTick;
		}

		//Optional to update the batch, could be moved to automatically update every batch creation
		//_SpriteBatcher.setNewBatch(_SpriteManager.getSprites());

		renderGame();
	}
}

void MainGame::renderGame() {
	std::vector<GameEngine::FontBatcher>* fonts = _StagingManager.getFonts();
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

	_fontBatcher_sans16.renderBatch();

	for(auto& font : *fonts) {
		font.renderBatch();
	}

	_ShadingProgram.unuse();

	glBindTexture(GL_TEXTURE_2D, 0);

	_Window.swapBuffer();
}

void MainGame::close() {
	std::cout << "Closing program." << std::endl;
	if (_IOThread.joinable()) {
		_IOThread.join();
	} else {
		_IOThread.~thread();
	}

	_Window.destroySDLWindow();
	SDL_Quit();

	_IOManager.saveOptions(_options);
	//int a;
	//std::cout << "Enter a key to close. ";
	//std::cin >> a;
}