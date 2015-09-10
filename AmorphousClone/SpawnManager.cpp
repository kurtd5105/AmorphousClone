#include "SpawnManager.h"

SpawnManager::SpawnManager()
{
}


SpawnManager::~SpawnManager()
{
}

void SpawnManager::init(int width, int height, int size, GameEngine::SpriteManager* manager) {
	_size = size;
	_width = width;
	_height = height;
	_SpriteManager = manager;
	_startTime = 0;
	_delayTime = random(1000, 4000);
}

void SpawnManager::startSpawn() {
	int diffrence = SDL_GetTicks() - _startTime;

	if (diffrence > _delayTime) {
		spawn(0);
		_delayTime = random(1000, 4000);
		_startTime = SDL_GetTicks();
	}
}

void SpawnManager::spawn(int enemy) {
	double x = random(0, _width);
	double y = random(0, _height);
	if (enemy == 0) {
		printf("Create an enemy here");
		_enemies.emplace_back();
		_enemies.back().init(float(x), float(y), 50.0f, 50.0f, 1.0f, std::vector<float>{}, "Textures/example_enemy.png", _SpriteManager);
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
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(a, b);
	return dist(mt);
}