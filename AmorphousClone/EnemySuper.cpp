#include "EnemySuper.h"
#include <iostream>

EnemySuper::EnemySuper() : _enabled(false) {
}


EnemySuper::~EnemySuper() {
}

void EnemySuper::init(float x, float y, float width, float height, float depth, int side, 
					  std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager, GameEngine::Random* Random) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_depth = depth;
	_radius = width / 2;
	_speed = ENEMY_SPEED;
	_SpriteManager = manager;
	//Assumes player is a circle
	_sprite = _SpriteManager->addSprite(x, y, width, height, depth, UVmM, path);
	_hitbox.init(x, y, width, height, _radius);
	_chance = 0.90f;
	_Random = Random;
	_isInit = true;
	//logicInit(side);
}

void EnemySuper::moveToTarget(float speed) {
	if(_enabled) {
		if(getPos() != _target) {
			glm::vec2 distanceTo = getCentered() - _target;
			//std::cout << distanceTo.x << ", " << distanceTo.y << std::endl;
			_sprite->pointAt(_target);
			float angle = getRotation();
			//Normalize later

			float xMove = 0;
			float yMove = 0;

			xMove = cos(angle) * _speed * speed;
			if(xMove >= abs(distanceTo.x)) {
				xMove = distanceTo.x;
				_x = _target.x;
			} else {
				_x += xMove;
			}
			yMove = sin(angle) * _speed * speed;
			if(yMove >= abs(distanceTo.y)) {
				yMove = distanceTo.y;
				_y = _target.y;
			} else {
				_y += yMove;
			}
			
			_sprite->translate(xMove, yMove);
			//this->translate(xMove, yMove, speed);
		} else {
			std::cout << "Deleting sprite." << std::endl;
			//Causes list iterator not incrementable error
			//_SpriteManager->deleteSprite(_sprite);
			_enabled = false;
		}
	}
}