#include "MainGame.h"


MainGame::MainGame() : _gameState(MAIN_MENU) {
}


MainGame::~MainGame() {
}

void MainGame::startGame() {
	//Vector containing all the textures needed, and whether or not they can be loaded asynchronously
	//MUST BE SORTED NON-ASYNC FIRST
	TEXTURE_LIST.emplace_back("Textures/hello_world.png", false);

	init();
	gameLoop();
	close();
}

void MainGame::init() {
	_Window.createWindow(800, 600, "Amorphous Clone", GameEngine::WindowMode::WINDOWED);

	//Load textures into memory, either they are loaded at the start of the game or not and we track
	//the status of the rest of the textures
	int i = 0;
	std::vector<bool> loadedFile;
	for(auto& file : TEXTURE_LIST) {
		if(file.async) {
			loadedFile.push_back(false);
			//_ResourceManager.asyncLoadTexture(file.path, loadedFile[i]._Getptr());
		} else {
			_ResourceManager.syncLoadTexture(file.path);
		}
	}

	//Temporary sprite creation, will be managed by the game logic in the future
	_sprites.emplace_back(0.0f, 0.0f, 100.0f,  100.0f, 1.0f, "Textures/hello_world.png", &_ResourceManager);
	_sprites.emplace_back(100.0f, 0.0f, 100.0f, 100.0f, 1.0f, "Textures/hello_world.png", &_ResourceManager);

	for(auto& sprite : _sprites) {
		_SpriteManager.addSprite(&sprite);
	}

	_ShadingProgram.init("Shaders/shader.vert", "Shaders/shader.frag", &_IOManager);

	_SpriteBatcher.init();
	_SpriteBatcher.setNewBatch(_SpriteManager.getSprites());
}

void MainGame::gameLoop() {
	while(_gameState != GameState::EXIT) {
		processInput();
		renderGame();
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

void MainGame::renderGame() {
	//Clear the screen
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Start using the shading program
	//_ShadingProgram.use();

	glActiveTexture(GL_TEXTURE0);

	//Get the texture uniform
	//GLint textureLocation = _ShadingProgram.getUniformLocation("playerTexture");
	//glUniform1i(textureLocation, 0);

	//Get the position uniform
	//GLint positionLocation = _colorProgram.getUniformLocation("P");
	//glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	//glUniformMatrix4fv(positionLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	_SpriteBatcher.cleanUp();
	_SpriteBatcher.setupBatches();
	_SpriteBatcher.renderBatch();

	//_ShadingProgram.unuse();

	glBindTexture(GL_TEXTURE_2D, 0);

	_Window.swapBuffer();
}

void MainGame::close() {
	_Window.destroySDLWindow();
	SDL_Quit();
}