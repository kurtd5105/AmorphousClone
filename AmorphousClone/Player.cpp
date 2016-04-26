#include "Player.h"

Player::Player(): _knockback(false), _invincible(false), _step(0.0f), _prevStep(0.0f), _targetRotation(0.0f), _gloopleBumps(0) {}

Player::~Player() {}

void Player::init(float x, float y, float width, float height, float depth, glm::vec2 scalingFactors, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_depth = depth;
	_radius = width / 2;
	_speed = PLAYER_SPEED;
	_SpriteManager = manager;
	//Assumes player is a circle
	_sprite = _SpriteManager->addSprite(x, y, width, height, depth, UVmM, path);
	_hitbox.init(x, y, width, height, _radius, GameEngine::CIRC);
	_sword.init(_x, _y, _rotation, scalingFactors, manager);
	_subAgents.push_back(&_sword);
	_isInit = true;
}

void Player::onCollide(EnemyType type, float targetRotation) {
	if(type == GOOPLE) {
		_gloopleBumps++;
	} else if(type == STICKIE) {
		_isSlowed = true;
	} else if(type == STICKIE_GOO) {
		_isSlowed = true;
		return;
	}

	if(_gloopleBumps >= 3) {
		_alive = false;
	} else if(!_invincible && !_knockback) {
		_knockback = true;
		_invincible = true;
		_targetRotation = targetRotation;
	}
}

void Player::knockback(float step) {
	_prevStep = _step;
	_step += step;
	if(_step <= KNOCKBACK_TIME) {
		if(_step > INVULNERABLE_TIME) {
			_invincible = false;
		}

		float xMove = cos(_targetRotation) * KNOCKBACK_SPEED * step;
		float yMove = sin(_targetRotation) * KNOCKBACK_SPEED * step;

		_x += xMove;
		_y += yMove;
		_sprite->translate(xMove, yMove);
		_sword.translate(xMove, yMove, 1.0f);
	} else {
		if(_prevStep <= KNOCKBACK_TIME) {
			float xMove = cos(_targetRotation) * KNOCKBACK_SPEED * (KNOCKBACK_TIME - _prevStep);
			float yMove = sin(_targetRotation) * KNOCKBACK_SPEED * (KNOCKBACK_TIME - _prevStep);

			_x += xMove;
			_y += yMove;
			_sprite->translate(xMove, yMove);
			_sword.translate(xMove, yMove, 1.0f);
		}
		_knockback = false;
		_invincible = false;
		_step = _prevStep = 0.0f;
	}
}
