#include "EnemySuper.h"

EnemySuper::EnemySuper(): _chance(0.0f), _collided(false), _hasGoo(false), _Random(nullptr), _goo(nullptr) {}


EnemySuper::~EnemySuper() {}

void EnemySuper::init(float x, float y, float width, float height, float depth, int side, 
					  std::vector<float> UVmM, std::string path, std::string slowFx, GameEngine::SpriteManager* manager, GameEngine::Random* Random) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_depth = depth;
	_radius = width / 2;
	_speed = ENEMY_SPEED;
	_SpriteManager = manager;
	//Assumes enemy is a circle
	_sprite = _SpriteManager->addSprite(x, y, width, height, depth, UVmM, path);
	_slowedEffect = _SpriteManager->addSprite(x, y, width, height, depth, UVmM, slowFx);
	_slowedEffect->setInvisible();
	_subSprites.push_back(_slowedEffect);
	_hitbox.init(x, y, width, height, _radius, GameEngine::CIRC);
	_chance = 0.90f;
	_Random = Random;
	_isInit = true;
	//logicInit(side);
}

void EnemySuper::moveToTarget(float speed) {
	if(_enabled) {
		if(getPos() != _target) {
			//Get the distance to the target and point at it
			auto distanceTo = getCentered() - _target;
			_sprite->pointAt(_target);
			auto angle = getRotation();

			float xMove, yMove;

			//Prevent the target from being overshot
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
			_SpriteManager->deleteSprite(_sprite);
			_sprite = nullptr;
			_enabled = false;
		}
	}
}

void EnemySuper::kill() {
	disable();
	setInvisible();
	_alive = false;
	for(unsigned int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->kill();
	}
	if(_hasGoo) {
		_goo = new StickieGoo(_x, _y, _width, _height, 50.0f, std::vector<float>{}, "Textures/StickieGoo.png", _SpriteManager);
	}
}
