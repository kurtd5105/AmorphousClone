#pragma once

#include <SDL/SDL.h>

#include <random>
#include <vector>

#include <GameEngine/IOManager.h>
#include <GameEngine/Random.h>

#include "EnemySuper.h"
#include "Stickie.h"

class SpawnManager
{
public:
	SpawnManager();
	~SpawnManager();

	void init(int width, int height, glm::vec2 scalingFactors, unsigned int size, GameEngine::SpriteManager* manager);

	bool spawn();

	std::list<EnemySuper>* getEnemies() { return &_enemies; }
	std::list<Goople>* getGooples() { return &_gooples; }
	std::list<Stickie>* getStickies() { return &_stickies; }

	unsigned int getEnemiesRemaining() const { return _size - _currIndex; }
	unsigned int getEnemiesKilled() const { return _enemiesKilled;  }

private:
	GameEngine::IOManager* _IOManager;
	GameEngine::SpriteManager* _SpriteManager;
	
	int _height, _width, _spritewidth, _spriteheight, _enemiesKilled;
	unsigned int _size, _currIndex;
	std::string enemytexture;
	glm::vec2 _scalingFactors;

	std::list<EnemySuper> _enemies;

	std::list<Goople> _gooples;
	std::list<Stickie> _stickies;
	std::vector<int> _spawnTimes;

	std::list<EnemySuper>::iterator _currEnemy;

	Uint32 _startTime, _lastSpawn;

	GameEngine::Random _Random;

	struct enemyinfo {
		EnemyType type;
		int _spawnrate;
		float _size;
		std::string _texture;
	};

	std::vector<enemyinfo> _enemyAlmanac;

	void gradientControl();

	SpawnManager::enemyinfo weightedRand();
	void createSpawn(struct enemyinfo);
	EnemySuper SpawnManager::enemyFactory(struct enemyinfo enemy, int side);
};
