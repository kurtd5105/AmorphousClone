#include "Goople.h"
#include "SpawnManager.h"
#include "Stickie.h"
#include <GameEngine/IOManager.h>
#include <GameEngine/SpriteInfo.h>
#include <GameEngine/SpriteManager.h>

#include <memory>
//#include <iostream>

//empty float vector
#define VEC_F_E std::vector<float>{}

SpawnManager::SpawnManager() : _IOManager(nullptr), _SpriteManager(nullptr), _height(0), _width(0), _spritewidth(0), _spriteheight(0),
_size(0), _currIndex(0), _startTime(0), _lastSpawn(0) {}


SpawnManager::~SpawnManager(){}

void SpawnManager::init(int width, int height, glm::vec2 scalingFactors, unsigned int size, GameEngine::SpriteManager* manager) {
	_size = size;
	_width = width;
	_height = height;
	_scalingFactors = scalingFactors;
	_Random.setScreenDimensions(_width, _height);
	_SpriteManager = manager;

	groupSpawn();

	_currEnemy = _enemies.begin();
	_lastSpawn = _startTime;
	_startTime = SDL_GetTicks();
	_currentSize = 0;
}

void SpawnManager::groupSpawn() {
	gradientControl();

	//Create spawn times for each enemy and create them
	for (unsigned int i = 0; i <= 10; i++) {
		_spawnTimes.push_back(_Random.randomInt(500, 2000));
		//Decide on enemy to spawn
		createSpawn(weightedRand());
	}
	//Cluster of enemies to be spawned
	_currentSize += 10;
}

bool SpawnManager::spawn() {
	if(_currEnemy != _enemies.end()) {
		auto curr = SDL_GetTicks();

		//Enable the next enemy if enough time has elapsed
		if(int(curr - _lastSpawn) >= _spawnTimes[_currIndex]) {
			_currEnemy->enable();
			_currEnemy->setVisible();
			_currEnemy = std::next(_currEnemy);
			_currIndex++;
			_lastSpawn = curr;
		}
		if(_currIndex >= _currentSize) {
			groupSpawn();
		}
		return true;
	}
	return false;
}

void SpawnManager::gradientControl() {
	int timeElapsed = (SDL_GetTicks() - _startTime) / 1000;

	//Gloople instantiation data
	struct enemyinfo gloople = {GOOPLE, 90, 50.0f, "Textures/example_enemy.png", "Textures/slowed.png"};
	_enemyAlmanac.push_back(gloople);

	//Time based eneny spawns
	if (timeElapsed >= 5) {
		struct enemyinfo stickie = {STICKIE, 50, 50, "Textures/stickie.png", "Textures/slowed.png"};
		_enemyAlmanac.push_back(stickie);
	}

	//Enemies killed based enemy spawns
	if (_enemiesKilled >= 20) {
		//Biters can spawn now
	}
}

SpawnManager::enemyinfo SpawnManager::weightedRand() {
	int weights = 0;

	for (auto& enemy : _enemyAlmanac) {
		weights += enemy._spawnrate;
	}
	int rand = _Random.randomInt(0, weights);

	for (auto& enemy : _enemyAlmanac) {
		if (rand < enemy._spawnrate)
			//std::cout << "making a: " << enemy._name << std::endl;
			return enemy;
		rand -= enemy._spawnrate;
	}
	//Should never reach, make a Gloople
	return _enemyAlmanac.front();
}

void SpawnManager::createSpawn(struct enemyinfo enemy) {
	float x = _Random.random(0.0f, float(_width));
	float y = _Random.random(0.0f, float(_height));
	//std::cout << "Enemy created, total: " << _enemies.size() + 1 << std::endl;

	int side = _Random.randomInt(0, 4);

	std::string _texture = enemy._texture;
	
	//Assumption height and width are equal (circle shaped enemy)
	auto _size = enemy._size;

	//Create the correct enemy type
	_enemies.push_back(enemyFactory(enemy, side));
	
	std::unique_ptr<GameEngine::SpriteInfo> info;
	//Spawn on the correct side
	if(side == 0) {
		info = std::make_unique<GameEngine::SpriteInfo>(x, float(_height), 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y, 2.0f, VEC_F_E, _texture, _SpriteManager);
		_enemies.back().init(info.get(), side, enemy._slowFx, &_Random);
	} else if(side == 1) {
		info = std::make_unique<GameEngine::SpriteInfo>(-_size, y, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y, 2.0f, VEC_F_E, _texture, _SpriteManager);
		_enemies.back().init(info.get(), side, enemy._slowFx, &_Random);
	} else if(side == 2) {
		info = std::make_unique<GameEngine::SpriteInfo>(float(_width), y, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y, 2.0f, VEC_F_E, _texture, _SpriteManager);
		_enemies.back().init(info.get(), side, enemy._slowFx, &_Random);
	} else {
		info = std::make_unique<GameEngine::SpriteInfo>(x, -_size, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y, 2.0f, VEC_F_E, _texture, _SpriteManager);
		_enemies.back().init(info.get(), side, enemy._slowFx, &_Random);
	}
	_enemies.back().setInvisible();
	_enemies.back().disable();
}

EnemySuper SpawnManager::enemyFactory(struct enemyinfo enemy, int side) {
	if (enemy.type == GOOPLE) {
		return Goople(side, &_Random, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y);
	}
	else if (enemy.type == STICKIE) {
		return Stickie(side, &_Random, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y);
	}
	else {
		//Return a Goople
		return Goople(side, &_Random, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y);
	}
}
