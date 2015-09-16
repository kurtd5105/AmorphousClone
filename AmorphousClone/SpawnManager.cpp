#include "SpawnManager.h"
#include <iostream>

SpawnManager::SpawnManager(){
}


SpawnManager::~SpawnManager(){
}

void SpawnManager::init(int width, int height, int size, GameEngine::SpriteManager* manager) {
	_size = size;
	_width = width;
	_height = height;
	_SpriteManager = manager;
	_startTime = 0;
	_mt.seed(time(nullptr));
	_delayTime = random(1000, 4000);

	//needs to be refactor later doesn't take into account dynamic sizes of sprites
	spriteheight = 50;
	spritewidth = 50;
}

void SpawnManager::startSpawn() {
	int difference = SDL_GetTicks() - _startTime;

	if (difference > _delayTime && _enemies.size() <= _size) {
		//add functionality for adding diffrent random enemies based on percentages
		spawn(0);
		_delayTime = random(1000, 4000);
		_startTime = SDL_GetTicks();
	}
}

void SpawnManager::spawn(int enemy) {
	double x = random(0, _width);
	double y = random(0, _height);
	//std::cout << "Enemy created, total: " << _enemies.size() + 1 << std::endl;

	double side = random(0, 4);

	//Which side of screen to spawn
	switch (int (side)) {
		case 0:
			//std::cout << "Up" << std::endl;
			_enemies.emplace_back();
			_enemies.back().init((float)x, _height, 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/example_enemy.png", _SpriteManager);
			break;
		case 1:
			//std::cout << "Left" << std::endl;
			_enemies.emplace_back();
			_enemies.back().init(-spritewidth, float(y), 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/example_enemy.png", _SpriteManager);
			break;
		case 2:
			//std::cout << "Right" << std::endl;
			_enemies.emplace_back();
			_enemies.back().init(_width, float(y), 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/example_enemy.png", _SpriteManager);
			break;
		case 3:
			//::cout << "Down" << std::endl;
			_enemies.emplace_back();
			_enemies.back().init((float)x, -spriteheight, 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/example_enemy.png", _SpriteManager);
			break;
	}
}

double SpawnManager::random(int a, int b) {
	std::uniform_real_distribution<double> dist(a, b);
	return dist(_mt);
}