#include "Sword.h"

Sword::Sword() {
}


Sword::~Sword() {
}

void Sword::init(float x, float y, float angle, GameEngine::SpriteManager* manager) {
	_x = x - 45.0f;
	_y = y + 15.0f;
	_width = 70.0f;
	_height = 20.0f;
	_rotation = angle;
	_speed = 0.5f;
	_rotationOffset = 3.927;//approximation of 5pi/4
	_SpriteManager = manager;
	//Constants, maybe they should be loaded some other way such as Player::giveSword and init a sword
	_sprite = _SpriteManager->addSprite(_x, _y, _width, _height, _depth, std::vector<float>{}, "Textures/sword.png");
	_sprite->setCenterOffset(std::vector<float>{1.0f, 0.0f});
	_isInit = true;
}

void Sword::attack() {
	//
}
