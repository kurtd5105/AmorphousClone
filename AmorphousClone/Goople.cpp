#include "Goople.h"
#include <iostream>
#include <random>

Goople::Goople(int side, GameEngine::Random* Random) : _hp(1){
	_Random = Random;
	logicInit(side);
}


Goople::~Goople(){
}

void Goople::logicInit(int side) {
	//0 top, 1 left, 2 right, 3 bottom
	int targetSide;
	if(side == 0) {
		targetSide = _Random->randomIntDist(std::discrete_distribution<int>{0, 1, 1, 1});
	} else if(side == 1) {
		targetSide = _Random->randomIntDist(std::discrete_distribution<int>{1, 0, 1, 1});
	} else if(side == 2) {
		targetSide = _Random->randomIntDist(std::discrete_distribution<int>{1, 1, 0, 1});
	} else if(side == 3) {
		targetSide = _Random->randomIntDist(std::discrete_distribution<int>{1, 1, 1, 0});
	}

	std::cout << "\tSide: " << side << " Randomed: " << targetSide << std::endl;

	if(targetSide == 0) {
		_target.x = _Random->random(0, _Random->screenWidth);
		_target.y = _Random->screenHeight + _height;
	} else if(targetSide == 1) {
		_target.x = -_width;
		_target.y = _Random->random(0, _Random->screenHeight);
	} else if(targetSide == 2) {
		_target.x = _Random->screenWidth + _width;
		_target.y = _Random->random(0, _Random->screenHeight);
	} else if(targetSide == 3) {
		_target.x = _Random->random(0, _Random->screenWidth);
		_target.y = -_height;
	}
}

void Goople::think() {

}

void Goople::onCollide() {

}
