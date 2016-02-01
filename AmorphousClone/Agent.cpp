#include "Agent.h"

#include <GameEngine/Errors.h>

Agent::Agent() : _x(0.0f), _y(0.0f), 
_width(0.0f), _height(0.0f), 
_depth(1.0f), 
_rotation(0.0f), _rotationOffset(0.0f),
_SpriteManager(nullptr), _sprite(nullptr),
_isInit(false), _visible(true), _enabled(true) {
}

Agent::~Agent() {
	if (_SpriteManager != nullptr && _sprite != nullptr) {
		_SpriteManager->deleteSprite(_sprite);
	}
	else if (_sprite != nullptr && _SpriteManager == nullptr) {
		GameEngine::fatalGenericError("Sprite deletion but no manager to delete with.");
	}
}

void Agent::translate(float x, float y, float speed) {
	if(_enabled) {
		_x += x * speed;
		_y += y * speed;
		_sprite->translate(x * speed, y * speed);
		//_hitbox.translate(x, y);
		for(unsigned int i = 0; i < _subAgents.size(); i++) {
			_subAgents[i]->translate(x, y, speed);
		}
	}
}

void Agent::rotate(float angle) {
	if(_enabled) {
		_rotation = angle;
		_sprite->rotate(angle);
		//_hitbox->rotate(angle);
		for(unsigned int i = 0; i < _subAgents.size(); i++) {
			_subAgents[i]->rotate(angle + _subAgents[i]->getRotationOffset());
		}
	}
}

void Agent::pointAt(glm::vec2 pos) {
	if(_enabled) {
		_sprite->pointAt(pos);
		_rotation = _sprite->getRotation();
		for(unsigned int i = 0; i < _subAgents.size(); i++) {
			_subAgents[i]->rotate(_rotation + _subAgents[i]->getRotationOffset());
			_subAgents[i]->lockOn(this);
		}
	}
}

void Agent::moveTo(Agent* agent, float speed) {
	if(_enabled) {
		glm::vec2 agentPos = agent->getPos();
		if(getPos() != agentPos) {
			_sprite->pointAt(agent->getCentered());
			float angle = getRotation();
			//Normalize later

			float xMove = 0;
			float yMove = 0;

			xMove = cos(angle) * _speed * speed;
			float offset = agentPos.x - _x;
			if(xMove > abs(offset)) {
				xMove = offset;
			}
			yMove = sin(angle) * _speed * speed;
			offset = agentPos.y - _y;
			if(yMove > abs(offset)) {
				yMove = offset;
			}

			_x += xMove;
			_y += yMove;
			_sprite->translate(xMove, yMove);
			//this->translate(xMove, yMove, speed);
		}
	}
}

void Agent::lockOn(Agent* agent) {
	if(_enabled) {
		//Refactor to get the angle relative between the current agent and the target then move to the center
		float rotation = _sprite->getRotation();
		_sprite->pointAt(agent->getCentered());
		float angle = getRotation();
		//Find the bottom left vector then use the angle to translate to the middle of that edge and use that as the before position
		glm::vec2 before = _sprite->getCentered();
		glm::vec2 pos = agent->getCentered();
		_x = pos.x;
		_y = pos.y;
		_sprite->translate(_x - before.x, _y - before.y);
		_sprite->rotate(rotation);
	}
}

void Agent::setInvisible() {
	_visible = false;
	_sprite->setInvisible();
	for(unsigned int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->setInvisible();
	}
}
void Agent::setVisible() {
	_visible = true;
	_sprite->setVisible();
	for(unsigned int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->setVisible();
	}
}

bool Agent::collideAgents(Agent* agent) {

	//Minimum distance for a collision to occur, can be diffrent of diffrent radiuses
	const float minDist = getRadius() + agent->getRadius();

	glm::vec2 centerA = getPos() + glm::vec2(getRadius());
	glm::vec2 centerB = agent->getPos() + glm::vec2(agent->getRadius());

	glm::vec2 diff = centerA - centerB;

	float distlength = glm::length(centerA - centerB);
	float depth = minDist - distlength;

	if (depth > 0) {
		printf("A collision occured\n");
		return true;
	}
	return false;

}

bool Agent::collideAgents(Agent* agent) {

	//Minimum distance for a collision to occur, can be diffrent of diffrent radiuses
	const float minDist = getRadius() + agent->getRadius();

	glm::vec2 centerA = getPos() + glm::vec2(getRadius());
	glm::vec2 centerB = agent->getPos() + glm::vec2(agent->getRadius());

	glm::vec2 diff = centerA - centerB;

	float distlength = glm::length(centerA - centerB);
	float depth = minDist - distlength;

	if (depth > 0) {
		//printf("A collision occured\n");
		return true;
	}
	return false;

}

void Agent::attack() {

}

void Agent::kill() {

}
