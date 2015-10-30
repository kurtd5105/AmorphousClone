#include "SpawnManager.h"
#include <iostream>

//empty float vector
#define VEC_F_E std::vector<float>{}

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
	_delayTime = _Random.random(1000.0f, 4000.0f);

	//needs to be refactor later doesn't take into account dynamic sizes of sprites
	spriteheight = 50;
	spritewidth = 50;
}

void SpawnManager::startSpawn() {
	int difference = SDL_GetTicks() - _startTime;

	if (difference > _delayTime && _enemies.size() <= _size) {
		//add functionality for adding diffrent random enemies based on percentages
		spawn(0);
		_delayTime = _Random.random(1000.0f, 4000.0f);
		_startTime = SDL_GetTicks();
	}
}

void SpawnManager::spawn(int enemy) {
	double x = _Random.random(0, _width);
	double y = _Random.random(0, _height);
	//std::cout << "Enemy created, total: " << _enemies.size() + 1 << std::endl;

	int side = _Random.randomInt(0, 4);

	//Which side of screen to spawn
	switch (int (side)) {
		case 0://top
			//std::cout << "Up" << std::endl;
			//_enemies.emplace_back();
			_enemies.push_back(Goople(0, &_Random));
			_enemies.back().init((float)x, _height, 50.0f, 50.0f, 1.0f, side, VEC_F_E, "Textures/example_enemy.png", _SpriteManager, &_Random);
			break;
		case 1://left
			//std::cout << "Left" << std::endl;
			_enemies.push_back(Goople(1, &_Random));
			_enemies.back().init(-spritewidth, (float)y, 50.0f, 50.0f, 1.0f, side, VEC_F_E, "Textures/example_enemy.png", _SpriteManager, &_Random);
			break;
		case 2://right
			//std::cout << "Right" << std::endl;
			_enemies.push_back(Goople(2, &_Random));
			_enemies.back().init(_width, (float)y, 50.0f, 50.0f, 1.0f, side, VEC_F_E, "Textures/example_enemy.png", _SpriteManager, &_Random);
			break;
		case 3://bottom
			//::cout << "Down" << std::endl;
			_enemies.push_back(Goople(3, &_Random));
			_enemies.back().init((float)x, -spriteheight, 50.0f, 50.0f, 1.0f, side, VEC_F_E, "Textures/example_enemy.png", _SpriteManager, &_Random);
			break;
	}
}