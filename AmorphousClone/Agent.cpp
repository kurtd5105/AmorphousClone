#include "Agent.h"

#include <GameEngine/Errors.h>
#include <iostream>

Agent::Agent() : _x(0.0f), _y(0.0f), _width(0.0f), _height(0.0f), _depth(1.0f), _rotation(0.0f), _radius(0.0f), _speed(0.0f), _rotationOffset(0.0f),
_isInit(false), _alive(true), _visible(true), _enabled(true), _isSlowed(false), _SpriteManager(nullptr), _sprite(nullptr), _slowedEffect(nullptr), _Random(nullptr) {}

Agent::~Agent() {
	if(_SpriteManager != nullptr) {
		if(_sprite != nullptr) {
			_SpriteManager->deleteSprite(_sprite);
		}
		if(_slowedEffect != nullptr) {
			_SpriteManager->deleteSprite(_slowedEffect);
		}
	} else if(_sprite != nullptr && _slowedEffect != nullptr) {
		GameEngine::fatalGenericError("Sprite deletion but no manager to delete with.");
	} else {
		//Optional output for debugging
		//std::cout << "No SpriteManager to delete sprites, but sprites are already deleted." << std::endl;
	}
}

void Agent::translate(float x, float y, float speed) {
	if(_enabled) {
		_x += x * speed;
		_y += y * speed;
		_sprite->translate(x * speed, y * speed);

		for(unsigned int i = 0; i < _subAgents.size(); i++) {
			_subAgents[i]->translate(x, y, speed);
		}
		for(unsigned int i = 0; i < _subSprites.size(); i++) {
			_subSprites[i]->translate(x * speed, y * speed);
		}
	}
}

void Agent::rotate(float angle) {
	if(_enabled) {
		_rotation = angle;
		_sprite->rotate(angle);

		for(unsigned int i = 0; i < _subAgents.size(); i++) {
			_subAgents[i]->rotate(angle + _subAgents[i]->getRotationOffset());
		}
		for(unsigned int i = 0; i < _subSprites.size(); i++) {
			_subSprites[i]->rotate(angle);
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
		for(unsigned int i = 0; i < _subSprites.size(); i++) {
			_subSprites[i]->pointAt(pos);
		}
	}
}

void Agent::moveTo(Agent* agent, float speed) {
	if(_enabled) {
		glm::vec2 agentPos = agent->getPos();
		if(getPos() != agentPos) {
			_sprite->pointAt(agent->getCentered());
			auto angle = getRotation();
			//Normalize later

			float xMove, yMove;

			xMove = cos(angle) * _speed * speed;
			auto offset = agentPos.x - _x;
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
		auto rotation = _sprite->getRotation();
		_sprite->pointAt(agent->getCentered());
		//auto angle = getRotation();
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
	for(unsigned int i = 0; i < _subSprites.size(); i++) {
		_subSprites[i]->setInvisible();
	}
}
void Agent::setVisible() {
	_visible = true;
	_sprite->setVisible();
	for(unsigned int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->setVisible();
	}
	if(_isSlowed) {
		_slowedEffect->setVisible();
	}
}

void Agent::processTimers(float step) {
	if(_enabled) {
		if(_isSlowed) {
			_slowTimer += step;
			if(_slowTimer > SLOW_TIME) {
				_slowTimer = 0.0f;
				_isSlowed = false;
				_slowedEffect->setInvisible();
			}
		}
	}
}

bool Agent::collideAgents(Agent* agent) const {

	//Minimum distance for a collision to occur, can be diffrent of diffrent radiuses
	const auto minDist = getRadius() + agent->getRadius();

	auto centerA = getPos() + glm::vec2(getRadius());
	auto centerB = agent->getPos() + glm::vec2(agent->getRadius());

	auto diff = centerA - centerB;

	auto distlength = glm::length(diff);
	auto depth = minDist - distlength;

	//Replace this later with collision manager managed collisions
	if (depth > 0) {
		glm::vec2 depthVec = glm::normalize(diff) * distlength;
		//glm::vec2(_x, _y) += depthVec / 2.0f;
		agent->setPos(agent->getPos() - (depthVec / 2.0f));
		return true;
	}
	return false;

}

void Agent::attack(float step) {

}

void Agent::kill() {
	disable();
	setInvisible();
	_alive = false;
	for(unsigned int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->kill();
	}
	_slowedEffect->setAlpha(0);
}
