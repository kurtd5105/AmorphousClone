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
}

void SpawnManager::startSpawn() {
	int difference = SDL_GetTicks() - _startTime;

	if (difference > _delayTime) {
		spawn(0);
		_delayTime = random(1000, 4000);
		_startTime = SDL_GetTicks();
	}
}

void SpawnManager::spawn(int enemy) {
	double x = random(0, _width);
	double y = random(0, _height);
	if (enemy == 0) {
		std::cout << "Enemy created, total: " << _enemies.size() + 1 << std::endl;
		_enemies.emplace_back();
		_enemies.back().init((float)x, (float)y, 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/example_enemy.png", _SpriteManager);
	}
}

void SpawnManager::update() {
	if ((int)_enemies.size() <= _size) {
		//determine which enemy to spawn
		//refactor this
		spawn(0);
	}
}

double SpawnManager::random(int a, int b) {
	std::uniform_real_distribution<double> dist(a, b);
	return dist(_mt);
}