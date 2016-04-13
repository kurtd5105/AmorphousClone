#pragma once

#include <SDL/SDL.h>

#include <random>
#include <vector>

#include <GameEngine/IOManager.h>
#include <GameEngine/Random.h>

#include "EnemySuper.h"

class SpawnManager
{
public:
	SpawnManager();
	~SpawnManager();

	void init(int width, int height, glm::vec2 scalingFactors, unsigned int size, GameEngine::SpriteManager* manager);

	bool spawn();

	std::list<EnemySuper>* getEnemies() { return &_enemies; }

private:
	GameEngine::IOManager* _IOManager;
	GameEngine::SpriteManager* _SpriteManager;

	void enemyInit();
	
	int _height, _width, spritewidth, spriteheight;
	unsigned int _size, _currIndex;
	std::string enemytexture;
	glm::vec2 _scalingFactors;

	std::list<EnemySuper> _enemies;
	std::vector<int> _spawnTimes;

	std::list<EnemySuper>::iterator _currEnemy;

	Uint32 _startTime, _lastSpawn;

	GameEngine::Random _Random;

	struct enemyinfo {
		std::string _name;
		int _spawnrate;
		float _size;
		std::string _texture;
	};

	std::vector<enemyinfo> enemyalmanac;

	SpawnManager::enemyinfo weightedRand();
	void createSpawn(struct enemyinfo);
};
