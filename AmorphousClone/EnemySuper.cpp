#include "EnemySuper.h"

EnemySuper::EnemySuper()
{
}


EnemySuper::~EnemySuper()
{
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

void EnemySuper::moveToTarget() {
	if(getPos() != _target) {
		_sprite->pointAt(_target);
		float angle = getRotation();
		//Normalize later

		float xMove = 0;
		float yMove = 0;

		xMove = cos(angle) * _speed;
		float offset = _target.x - _x;
		if(xMove > abs(offset)) {
			xMove = offset;
		}
		yMove = sin(angle) * _speed;
		offset = _target.y - _y;
		if(yMove > abs(offset)) {
			yMove = offset;
		}

		_x += xMove;
		_y += yMove;
		_sprite->translate(xMove, yMove);
	}
}