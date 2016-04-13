#include "Player.h"

Player::Player(): _isAlive(true), _gloopleBumps(0) {}

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
	_hitbox.init(x, y, width, height, _radius);
	_sword.init(_x, _y, _rotation, scalingFactors, manager);
	_subAgents.push_back(&_sword);
	_isInit = true;
}

void Player::onCollide(EnemyType type) {
	if(type == GLOOPLE) {
		_gloopleBumps++;
		if(_gloopleBumps >= 3) {
			_isAlive = false;
		}
	}
}
