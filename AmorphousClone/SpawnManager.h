#pragma once

#include <SDL/SDL.h>

#include <random>
#include <vector>
#include <time.h>

#include <GameEngine/IOManager.h>
#include <GameEngine/Random.h>

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
	GameEngine::IOManager* _IOManager;
	GameEngine::SpriteManager* _SpriteManager;

	void spawn(int enemy);

	int _height, _width, _size, spritewidth, spriteheight;

	std::list<EnemySuper> _enemies;

	Uint32 _startTime;
	double _delayTime;

	//std::mt19937 _mt;
	GameEngine::Random _Random;
	//double random(int a, int b);
};
