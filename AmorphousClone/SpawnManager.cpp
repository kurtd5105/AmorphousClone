#include "SpawnManager.h"
#include "Goople.h"
#include "Stickie.h"
//#include <iostream>

//empty float vector
#define VEC_F_E std::vector<float>{}

SpawnManager::SpawnManager() : _IOManager(nullptr), _SpriteManager(nullptr), _height(0), _width(0), spritewidth(0), spriteheight(0),
_size(0), _currIndex(0), _startTime(0), _lastSpawn(0) {}


SpawnManager::~SpawnManager(){}

void SpawnManager::init(int width, int height, glm::vec2 scalingFactors, unsigned int size, GameEngine::SpriteManager* manager) {
	_size = size;
	_width = width;
	_height = height;
	_scalingFactors = scalingFactors;
	_Random.setScreenDimensions(_width, _height);
	_SpriteManager = manager;

	enemyInit();

	//Create spawn times for each enemy and create them
	for(unsigned int i = 0; i <= _size; i++) {
		_spawnTimes.push_back(_Random.randomInt(500, 2000));
		//Decide on enemy to spawn
		createSpawn(weightedRand());
	}
	_currEnemy = _enemies.begin();
	_startTime = SDL_GetTicks();
	_lastSpawn = _startTime;
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
		return true;
	}
	return false;
}

void SpawnManager::enemyInit() {
	//Instationation of enemy data struct, consists of spawnrate int, size of sprite int and string for texture

	//Gloople instantiation data
	struct enemyinfo gloople = { GLOOPLE, 90, 50.0f, "Textures/example_enemy.png" };
	struct enemyinfo stickie = { STICKIE, 10, 50, "Textures/stickie.png" };
	enemyalmanac.push_back(gloople);
	enemyalmanac.push_back(stickie);
}

SpawnManager::enemyinfo SpawnManager::weightedRand() {
	int weights = 0;

	for (auto& enemy : enemyalmanac) {
		weights += enemy._spawnrate;
	}
	int rand = _Random.randomInt(0, weights);

	for (auto& enemy : enemyalmanac) {
		if (rand < enemy._spawnrate)
			//std::cout << "making a: " << enemy._name << std::endl;
			return enemy;
		rand -= enemy._spawnrate;
	}
	//Should never reach, make a Gloople
	return enemyalmanac.front();
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
	if(enemy.type == GLOOPLE) {
		_enemies.push_back(Goople(side, &_Random, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y));
	} else if(enemy.type == STICKIE) {
		_enemies.push_back(Stickie(side, &_Random, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y));
	}
	
	//Spawn on the correct side
	if(side == 0) {
		_enemies.back().init(x, float(_height), 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y,
							 2.0f, side, VEC_F_E, _texture, _SpriteManager, &_Random);
	} else if(side == 1) {
		_enemies.back().init(-_size, y, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y,
							 2.0f, side, VEC_F_E, _texture, _SpriteManager, &_Random);
	} else if(side == 2) {
		_enemies.back().init(float(_width), y, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y,
							 2.0f, side, VEC_F_E, _texture, _SpriteManager, &_Random);
	} else {
		_enemies.back().init(x, -_size, 50.0f * _scalingFactors.y, 50.0f * _scalingFactors.y,
							 2.0f, side, VEC_F_E, _texture, _SpriteManager, &_Random);
	}
	_enemies.back().setInvisible();
	_enemies.back().disable();
}