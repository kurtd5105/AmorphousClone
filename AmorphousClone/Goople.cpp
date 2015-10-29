#include "Goople.h"


Goople::Goople() : _hp(1){
}


Goople::~Goople(){
}

void Goople::logicInit(int side) {
	//0 top, 1 left, 2 right, 3 bottom
	int targetSide = _Random->randomInt(0, 3);
	if(side == 0) {
		//_target.x = _Random->random(0, _Random->screenWidth);
		//_target.y = _Random->random(0, _Random->screenHeight/2.0f);
	}
}

void Goople::think() {

}

void Goople::onCollide() {

}
