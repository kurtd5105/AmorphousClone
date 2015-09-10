#pragma once
#pragma once

#include <SDL/SDL.h>

#include <random>
#include <vector>

#include "EnemySuper.h"
#include "Goople.h"

class SpawnManager
{
public:
	SpawnManager();
	~SpawnManager();

	void init(int width, int height, int size, GameEngine::SpriteManager* manager);

	void startSpawn();

	std::list<EnemySuper>* getEnemies() { return &_enemies; }

private:
	GameEngine::SpriteManager* _SpriteManager;

	void update();
	void spawn(int enemy);

	int _height, _width;
	int _size;

	std::list<EnemySuper> _enemies;

	Uint32 _startTime;
	double _delayTime;

	double random(int a, int b);
};
