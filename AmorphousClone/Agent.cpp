#include "Agent.h"

#include <GameEngine/Errors.h>

Agent::Agent() : _x(0), _y(0), _width(0), _height(0), _depth(0), _rotation(0), _SpriteManager(nullptr), _sprite(nullptr) {
}

Agent::~Agent() {
	if (_SpriteManager != nullptr && _sprite != nullptr) {
		_SpriteManager->deleteSprite(_sprite);
	}
	else if (_sprite != nullptr && _SpriteManager == nullptr) {
		GameEngine::fatalGenericError("Sprite deletion but no manager to delete with.");
	}
}

void Agent::translate(float x, float y) {
	_x += x;
	_y += y;
	_sprite->translate(x, y);
	//_hitbox.translate(x, y);
}

void Agent::rotate(float angle) {
	_rotation = angle;
	_sprite->rotate(angle);
	//_hitbox->rotate(angle);
}

void Agent::pointAt(glm::vec2 pos) {
	_sprite->pointAt(pos);
}

void Agent::attack() {

}

void Agent::kill() {

}
