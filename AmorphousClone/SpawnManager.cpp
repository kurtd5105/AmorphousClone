#include "SpawnManager.h"
#include "Goople.h"
//#include <iostream>

//empty float vector
#define VEC_F_E std::vector<float>{}

SpawnManager::SpawnManager() : _IOManager(nullptr), _SpriteManager(nullptr), _height(0), _width(0), spritewidth(0), spriteheight(0),
_size(0), _currIndex(0), _startTime(0), _lastSpawn(0) {}


SpawnManager::~SpawnManager(){}

void SpawnManager::init(int width, int height, unsigned int size, GameEngine::SpriteManager* manager) {
	_size = size;
	_width = width;
	_height = height;
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
	struct enemyinfo gloople = { "Gloople", 90, 50.0f, "Textures/example_enemy.png" };
	enemyalmanac.push_back(gloople);
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
	return enemyalmanac.back();
}

void SpawnManager::createSpawn(struct enemyinfo enemy) {
	float x = _Random.random(0.0f, float(_width));
	float y = _Random.random(0.0f, float(_height));
	//std::cout << "Enemy created, total: " << _enemies.size() + 1 << std::endl;

	int side = _Random.randomInt(0, 4);

	std::string _texture = enemy._texture;
	//Assumption height and width are equal
	auto _size = enemy._size;

	//Which side of screen to spawn
	switch (side) {
		case 0://top
			//std::cout << "Up" << std::endl;
			//_enemies.emplace_back();
			_enemies.push_back(Goople(0, &_Random, 50.0f, 50.0f));
			_enemies.back().init(float(x), float(_height), 50.0f, 50.0f, 2.0f, side, VEC_F_E, _texture, _SpriteManager, &_Random);
			_enemies.back().setInvisible();
			_enemies.back().disable();
			break;
		case 1://left
			//std::cout << "Left" << std::endl;
			_enemies.push_back(Goople(1, &_Random, 50.0f, 50.0f));
			_enemies.back().init(float(-_size), float(y), 50.0f, 50.0f, 2.0f, side, VEC_F_E, _texture, _SpriteManager, &_Random);
			_enemies.back().setInvisible();
			_enemies.back().disable();
			break;
		case 2://right
			//std::cout << "Right" << std::endl;
			_enemies.push_back(Goople(2, &_Random, 50.0f, 50.0f));
			_enemies.back().init(float(_width), float(y), 50.0f, 50.0f, 2.0f, side, VEC_F_E, _texture, _SpriteManager, &_Random);
			_enemies.back().setInvisible();
			_enemies.back().disable();
			break;
		case 3://bottom
			//::cout << "Down" << std::endl;
			_enemies.push_back(Goople(3, &_Random, 50.0f, 50.0f));
			_enemies.back().init(float(x), float(-_size), 50.0f, 50.0f, 2.0f, side, VEC_F_E, _texture, _SpriteManager, &_Random);
			_enemies.back().setInvisible();
			_enemies.back().disable();
			break;
	}
}