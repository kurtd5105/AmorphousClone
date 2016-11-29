#include "Agent.h"

#include <GameEngine/Errors.h>
#include <GameEngine/Random.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteManager.h>
#include <iostream>

Agent::Agent() : _x(0.0f), _y(0.0f), _width(0.0f), _height(0.0f), _depth(1.0f), _rotation(0.0f), _radius(0.0f), _speed(0.0f), _rotationOffset(0.0f), _slowTimer(0.0f),
_isInit(false), _alive(true), _visible(true), _enabled(true), _isSlowed(false), _SpriteManager(nullptr), _sprite(nullptr), _slowedEffect(nullptr), _Random(nullptr) {}

Agent::~Agent() {
	// If the sprite manager exists, then the main sprite and slowed effect may need to be deleted.
	if(_SpriteManager != nullptr) {
		// Delete the sprites from the sprite manager if the sprite exists.
		if(_sprite != nullptr) {
			_SpriteManager->deleteSprite(_sprite);
		}
		if(_slowedEffect != nullptr) {
			_SpriteManager->deleteSprite(_slowedEffect);
		}
	// If any sprite hasn't been deleted and the Sprite Manager doesn't exist then there was possibly an issue releasing the memory.
	} else if(_sprite != nullptr || _slowedEffect != nullptr) {
		GameEngine::fatalGenericError("Sprite deletion but no manager to delete with.");
	} else {
		// Optional output for debugging.
		//std::cout << "No SpriteManager to delete sprites, but sprites are already deleted." << std::endl;
	}
}

void Agent::translate(float x, float y, float speed) {
	// Translate the agent only if it's enabled.
	if(_enabled) {
		float dx = x * speed * (_isSlowed ? SLOW_MULT : 1.0f);
		float dy = y * speed * (_isSlowed ? SLOW_MULT : 1.0f);
		_x += dx;
		_y += dy;
		_sprite->translate(dx, dy);

		// Translate all sub-agents and sub-sprites.
		for(unsigned int i = 0; i < _subAgents.size(); i++) {
			_subAgents[i]->translate(x, y, speed);
		}
		for(unsigned int i = 0; i < _subSprites.size(); i++) {
			_subSprites[i]->translate(dx, dy);
		}
	}
}

void Agent::rotate(float angle) {
	// Rotate the agent only if it's enabled.
	if(_enabled) {
		_rotation = angle;
		_sprite->rotate(angle);

		// Rotate all sub-agents and sub-sprites.
		for(unsigned int i = 0; i < _subAgents.size(); i++) {
			_subAgents[i]->rotate(angle + _subAgents[i]->getRotationOffset());
		}
		for(unsigned int i = 0; i < _subSprites.size(); i++) {
			_subSprites[i]->rotate(angle);
		}
	}
}

void Agent::pointAt(glm::vec2 pos) {
	// Point the agent only if it's enabled.
	if(_enabled) {
		_sprite->pointAt(pos);
		_rotation = _sprite->getRotation();

		// For sub-agents, rotate them then lock them onto the agent. Drifting may occur from the rotation.
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
	// Move towards the other agent only if enabled.
	if(_enabled) {
		glm::vec2 agentPos = agent->getPos();

		// Make sure they aren't already on top of each other.
		if(getPos() != agentPos) {
			// Point towards the target agent.
			_sprite->pointAt(agent->getCentered());
			auto angle = getRotation();
			//Normalize later

			float xMove, yMove;

			// Calculate the maximum distance that the agent can move in the current step.
			xMove = cos(angle) * _speed * speed * (_isSlowed ? SLOW_MULT : 1.0f);
			auto offset = agentPos.x - _x;

			// Move less if needed.
			if(xMove > abs(offset)) {
				xMove = offset;
			}

			// Do the same for the y direction.
			yMove = sin(angle) * _speed * speed * (_isSlowed ? SLOW_MULT : 1.0f);
			offset = agentPos.y - _y;
			if(yMove > abs(offset)) {
				yMove = offset;
			}

			_x += xMove;
			_y += yMove;

			// Translate the main sprite.
			_sprite->translate(xMove, yMove);

			// Translate the sub-agents and sub-sprites.
			for(unsigned int i = 0; i < _subAgents.size(); i++) {
				_subAgents[i]->translate(xMove, yMove, 1.0f);
			}
			for(unsigned int i = 0; i < _subSprites.size(); i++) {
				_subSprites[i]->translate(xMove, yMove);
			}
		}
	}
}

void Agent::lockOn(Agent* agent) {
	// Only lock onto the other agent if enabled.
	if(_enabled) {
		//Refactor to get the angle relative between the current agent and the target then move to the center
		auto rotation = _sprite->getRotation();
		_sprite->pointAt(agent->getCentered());
		//auto angle = getRotation();

		//Find the bottom left vector then use the angle to translate to the middle of that edge and use that as the before position.
		glm::vec2 before = _sprite->getCentered();
		glm::vec2 pos = agent->getCentered();

		_x = pos.x;
		_y = pos.y;

		// Translate and rotate the sprite to be on top of the other agent.
		float dx = _x - before.x;
		float dy = _y - before.y;
		_sprite->translate(dx, dy);
		_sprite->rotate(rotation);

		// Lock the sub-agents and sub-sprites onto the agent as well.
		for(unsigned int i = 0; i < _subAgents.size(); i++) {
			_subAgents[i]->translate(dx, dy, 1.0f);
			_subAgents[i]->rotate(rotation);
		}
		for(unsigned int i = 0; i < _subSprites.size(); i++) {
			_subSprites[i]->translate(dx, dy);
			_subSprites[i]->rotate(rotation);
		}
	}
}

glm::vec2 Agent::getCentered() const
{
	return _sprite->getCentered();
}

void Agent::setInvisible() {
	_visible = false;
	_sprite->setInvisible();

	// Set the sub-agents and sub-sprites to be invisible.
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

	// Set the sub-agents and sub-sprites to be visible.
	for(unsigned int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->setVisible();
	}
	for(unsigned int i = 0; i < _subSprites.size(); i++) {
		_subSprites[i]->setVisible();
	}

	// If the agent isn't slowed then the slowed effect should remain invisible.
	if(!_isSlowed) {
		_slowedEffect->setInvisible();
	}
}

void Agent::processTimers(float step) {
	// Process the timers only if the agent is enabled.
	if(_enabled) {
		// Process the slow timer if slowed.
		if(_isSlowed) {
			_slowTimer += step;

			// If the agent has been slowed long enough then remove the slow effect.
			if(_slowTimer > SLOW_TIME) {
				_slowTimer = 0.0f;
				_isSlowed = false;
				_slowedEffect->setInvisible();
			}
		}
	}
}

void Agent::slow()
{
	_slowedEffect->setVisible();
	_isSlowed = true;
	_slowTimer = 0;
	for (auto& a : _subAgents) {
		a->slow();
	}
}

void Agent::setAlpha(GLubyte alpha)
{
	_sprite->setAlpha(alpha);
	for (auto& a : _subAgents) {
		a->setAlpha(alpha); 
	} 
	for (auto& s : _subSprites) {
		s->setAlpha(alpha);
	}
}

GLubyte Agent::getAlpha() const
{
	return _sprite->getAlpha();
}

bool Agent::collideAgents(Agent* agent) const {
	// TODO: Replace this function with Collision Manager.
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

void Agent::attack(float step) {}

void Agent::kill() {
	disable();
	setInvisible();
	_alive = false;

	// Kill all sub-agents.
	for(unsigned int i = 0; i < _subAgents.size(); i++) {
		_subAgents[i]->kill();
	}

	// Make all sub-sprites invisible.
	for(unsigned int i = 0; i < _subSprites.size(); i++) {
		_subSprites[i]->setInvisible();
	}
}

float Agent::getRotation() const
{
	return _sprite->getRotation();
}
