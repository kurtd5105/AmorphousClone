#pragma once
#include <GL/glew.h>
#include <SDL/SDL.h>

#include <GameEngine/Window.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/IOManager.h>
#include <GameEngine/ResourceManager.h>
#include <GameEngine/ShadingProgram.h>
#include <GameEngine/SpriteManager.h>
#include <GameEngine/SpriteBatcher.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/Camera.h>

enum GameState {
	MAIN_MENU, PLAYING, EXIT
};

class TextureInfo {
public:
	std::string path;
	bool async;

	TextureInfo(std::string givenPath, bool givenAsync) {
		path = givenPath;
		async = givenAsync;
	}
};

class MainGame {
public:
	MainGame();
	~MainGame();

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	//Vector containing all the textures needed, and whether or not they can be loaded asynchronously
	//MUST BE SORTED NON-ASYNC FIRST
	std::vector<TextureInfo> TEXTURE_LIST = std::vector<TextureInfo>{TextureInfo("Textures/hello_world.png", false)};

	std::vector<std::string> SHADING_ATTRIBUTES = std::vector<std::string>{"vertexPosition", "vertexColor", "vertexUV"};

	void startGame();
	void init();
	
	void gameLoop();

	void processInput();
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

	GameState _gameState;

	std::vector<GameEngine::Sprite> _sprites;
};

