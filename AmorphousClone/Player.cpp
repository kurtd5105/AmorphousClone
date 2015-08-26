#include "Player.h"


Player::Player() : _x(0), _y(0) {
}


Player::~Player() {
}

void Player::init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_depth = depth;
	_SpriteManager = manager;
	_sprite = _SpriteManager->addSprite(x, y, width, height, depth, UVmM, path);
	_hitbox.init(x, y, width, height, width/2);
}

void Player::translate(float x, float y) {
	_x += x;
	_y += y;
	_sprite->translate(x, y);
	_hitbox.translate(x, y);
}

void Player::attack() {

}

void Player::kill() {

}