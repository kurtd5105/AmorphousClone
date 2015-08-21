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

	//_ResourceManager.asyncLoadTexture(std::vector<std::string>{"Textures/01.png", "Textures/02.png", "Textures/03.png"}, _IOThread, &_IOThreadState);

	//_ResourceManager.asyncLoadTexture(TEXTURE_LIST_ASYNC, _IOThread, &_IOThreadState);
	_SpriteManager.init(GameEngine::sortType::TEXTURE, &_ResourceManager);

	//Temporary sprite creation, will be managed by the game logic in the future
	_SpriteManager.addSprite(0.0f, 0.0f, 100.0f, 100.0f, 1.0f, "Textures/hello_world.png");
	_SpriteManager.addSprite(100.0f, 0.0f, 100.0f, 200.0f, 1.0f, "Textures/hello_world.png");
	_SpriteManager.addSprite(0.0f, 100.0f, 100.0f, 100.0f, 1.0f, "Textures/hello_world.png");

	_ShadingProgram.init("Shaders/shader.vert", "Shaders/shader.frag", SHADING_ATTRIBUTES, &_IOManager);

	_Camera.init(WINDOW_WIDTH, WINDOW_HEIGHT);

	_SpriteBatcher.init();
	_SpriteBatcher.setNewBatch(_SpriteManager.getSprites());
}

void MainGame::gameLoop() {
	while(_gameState != GameState::EXIT) {
		processInput();

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

	//Handle input here

	//Temporary camera movement code
	Uint8 KEY_A = SDL_SCANCODE_A;
	Uint8 KEY_D = SDL_SCANCODE_D;
	Uint8 KEY_W = SDL_SCANCODE_W;
	Uint8 KEY_S = SDL_SCANCODE_S;
	if((keys[KEY_D] != keys[KEY_A]) && (keys[KEY_W] != keys[KEY_S])) {
		//If there is diagonal movement then normalize it so the distance moved is still camera speed * 1
		_Camera.setPosition(_Camera.getPosition() + glm::vec2(_Camera.CAMERA_SPEED * (keys[KEY_D] - keys[KEY_A]) / sqrt(2), _Camera.CAMERA_SPEED*(keys[KEY_W] - keys[KEY_S]) / sqrt(2)));
	} else {
		//Move the camera by the additions of the key presses
		_Camera.setPosition(_Camera.getPosition() + glm::vec2(_Camera.CAMERA_SPEED * (keys[KEY_D] - keys[KEY_A]), _Camera.CAMERA_SPEED*(keys[KEY_W] - keys[KEY_S])));
	}
	_Camera.setScale(_Camera.getScale() + _Camera.SCALE_SPEED * (keys[SDL_SCANCODE_Q] - keys[SDL_SCANCODE_E]));
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
}