#pragma once

#include <SDL/SDL.h>

#include <random>
#include <vector>
//#include <time.h>

#include <GameEngine/IOManager.h>
#include <GameEngine/Random.h>

#include "EnemySuper.h"
#include "Goople.h"

class SpawnManager
{
public:
	SpawnManager();
	~SpawnManager();

	void init(int width, int height, unsigned int size, GameEngine::SpriteManager* manager);

	void spawn();

	std::list<EnemySuper>* getEnemies() { return &_enemies; }

private:
	GameEngine::IOManager* _IOManager;
	GameEngine::SpriteManager* _SpriteManager;

	void createSpawn(int enemy);

	int _height, _width, spritewidth, spriteheight;
	unsigned int _size, _currIndex;

	std::list<EnemySuper> _enemies;
	std::vector<int> _spawnTimes;

	std::list<EnemySuper>::iterator _currEnemy;

	Uint32 _startTime, _lastSpawn;

	GameEngine::Random _Random;
};
