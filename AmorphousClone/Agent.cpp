#include "Agent.h"

#include <GameEngine/Errors.h>

Agent::Agent() : _x(0.0f), _y(0.0f), 
_width(0.0f), _height(0.0f), 
_depth(1.0f), 
_rotation(0.0f), _rotationOffset(0.0f),
_SpriteManager(nullptr), _sprite(nullptr),
_isInit(false) {
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
	/*for(auto& agent : _subAgents) {
		agent.translate(x, y);
	}*/
	for(int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->translate(x, y);
	}
}

void Agent::rotate(float angle) {
	_rotation = angle;
	_sprite->rotate(angle);
	//_hitbox->rotate(angle);
	/*for(auto& agent : _subAgents) {
		agent.rotate(angle);
	}*/
	for(int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->rotate(angle + _subAgents[i]->getRotationOffset());
	}
}

void Agent::pointAt(glm::vec2 pos) {
	_sprite->pointAt(pos);
	_rotation = _sprite->getRotation();
	/*for(auto& agent : _subAgents) {
		agent.rotate(_rotation);
	}*/
	for(int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->rotate(_rotation + _subAgents[i]->getRotationOffset());
		_subAgents[i]->lockOn(this);
	}
}

void Agent::moveTo(Agent* agent) {
	_sprite->pointAt(agent->getCentered());
	float angle = getRotation();
	//Normalize later
	float xMove = cos(angle) * _speed;
	float yMove = sin(angle) * _speed;
	_x += xMove;
	_y += yMove;
	_sprite->translate(xMove, yMove);
}

void Agent::lockOn(Agent* agent) {
	//Refactor to get the angle relative between the current agent and the target then move to the center
	float rotation = _sprite->getRotation();
	_sprite->pointAt(agent->getCentered());
	float angle = getRotation();
	//Translate to the center and subtract the radius of the center to offset it
	//float xMove = (cos(angle) * _speed) - (acos(angle) * 35.0f);
	//float yMove = (sin(angle) * _speed) - (asin(angle) * 35.0f);
	//_x += xMove;
	//_y += yMove;
	//Find the bottom left vector then use the angle to translate to the middle of that edge and use that as the before position
	glm::vec2 before = _sprite->getCentered();
	glm::vec2 pos = agent->getCentered();
	_x = pos.x;
	_y = pos.y;
	_sprite->translate(_x - before.x, _y - before.y);
	//_sprite->translate(xMove, yMove);
	_sprite->rotate(rotation);
}

void Agent::attack() {

}

void Agent::kill() {

}
