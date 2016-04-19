#include "Sword.h"

Sword::Sword(): _step(0.0f), _isActive(false) {
}


Sword::~Sword() {
}

void Sword::init(float x, float y, float angle, glm::vec2 scalingFactors, GameEngine::SpriteManager* manager) {
	_x = x - 45.0f;
	_y = y + 15.0f;
	_width = 140.0f * scalingFactors.y;
	_height = 20.0f * scalingFactors.y;
	_rotation = angle;
	_speed = 0.5f;
	_rotationOffset = 3.927f;//approximation of 5pi/4
	_SpriteManager = manager;
	//Constants, maybe they should be loaded some other way such as Player::giveSword and init a sword
	_sprite = _SpriteManager->addSprite(_x, _y, _width, _height, _depth, std::vector<float>{}, "Textures/sword.png");
	_sprite->setCenterOffset(std::vector<float>{1.0f, 0.0f});
	_isInit = true;
}

void Sword::attack(float step) {
	_step += step;
	if(_step <= ATTACK_HALF_TIME) {
		_rotationOffset = 3.927f + (ATTACK_HALF * _step);
	} else if(_step <= ATTACK_HALF_TIME * 2.0f) {
		_rotationOffset = 3.927f + (float(M_PI) - (ATTACK_HALF * (_step - ATTACK_HALF_TIME)));
	} else if(_step != 0.0f) {
		_step = 0.0f;
		_rotationOffset = 3.927f;
		_isActive = false;
	}
}
