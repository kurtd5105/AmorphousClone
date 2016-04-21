#include "Stickie.h"
#include <random>

Stickie::Stickie(int side, GameEngine::Random* Random, float width, float height) : _hp(1) {
	_Random = Random;
	_type = STICKIE;
	_speed = 1.5f;
	logicInit(side, width, height);
}


Stickie::~Stickie() {
}

void Stickie::logicInit(int side, float width, float height) {
	//0 top, 1 left, 2 right, 3 bottom
	int targetSide = 0;
	if(side == 0) {
		targetSide = _Random->randomIntDist(std::discrete_distribution<int>{0, 1, 1, 1});
	} else if(side == 1) {
		targetSide = _Random->randomIntDist(std::discrete_distribution<int>{1, 0, 1, 1});
	} else if(side == 2) {
		targetSide = _Random->randomIntDist(std::discrete_distribution<int>{1, 1, 0, 1});
	} else if(side == 3) {
		targetSide = _Random->randomIntDist(std::discrete_distribution<int>{1, 1, 1, 0});
	}

	//std::cout << "\tSide: " << side << " Randomed: " << targetSide << std::endl;

	if(targetSide == 0) {
		_target.x = float(_Random->randomInt(0, _Random->screenWidth));
		_target.y = _Random->screenHeight + (2 * height);
	} else if(targetSide == 1) {
		_target.x = -(2 * width);
		_target.y = float(_Random->randomInt(0, _Random->screenHeight));
	} else if(targetSide == 2) {
		_target.x = _Random->screenWidth + (2 * width);
		_target.y = float(_Random->randomInt(0, _Random->screenHeight));
	} else if(targetSide == 3) {
		_target.x = float(_Random->randomInt(0, _Random->screenWidth));
		_target.y = -(2 * height);
	}
}

void Stickie::think() {}

void Stickie::onCollide() {}

void Stickie::kill() {
	disable();
	setInvisible();
	_alive = false;
	for(unsigned int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->kill();
	}
}
