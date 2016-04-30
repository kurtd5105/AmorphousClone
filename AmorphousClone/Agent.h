#pragma once

#include <GameEngine/SpriteManager.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/Hitbox.h>
#include <GameEngine/Random.h>

class EnemySuper;
class Goople;
class Stickie;
class Player;

// Defines required capabilities of all agents. It is not meant to be instantiated.
class Agent {
public:
	Agent();
	virtual ~Agent();

	// Translates the agent, the agent's sub-agents and the agent's sub-sprites by a given amount and multiplied by the speed and
	// slowed by the goo if the agent is currently under its effects.
	virtual void translate(float x, float y, float speed);

	// Rotates the agent, all sub-agents and sub-sprites by the angle given in radians.
	void rotate(float angle);

	// Makes the agent, all sub-agents and sub-sprites point at a given point.
	void pointAt(glm::vec2 pos);

	// Moves the agent towards another agent at a given speed, and slowed by goo if under its effects. Moves until the agent is
	// on top of the other agent.
	void moveTo(Agent* agent, float speed);

	// Directly moves the agent onto the given agent. Not affected by speed.
	void lockOn(Agent* agent);

	// Used to collide two agents together.
	// TODO: use collision manager instead.
	bool collideAgents(Agent *agent) const;

	// A function to be overridden that is used when an attack animation is triggered.
	virtual void attack(float step);

	// A basic function that will make the agent invisible and disabled as well as all sub-agents and sub-sprites.
	virtual void kill();

	// Returns the rotation of the main sprite.
	float getRotation() const { return _sprite->getRotation(); }

	// Returns the agent's rotation offset from its current angle.
	float getRotationOffset() const { return _rotationOffset; }

	// Returns the agent's radius. Radius will be 0 if the agent isn't circular.
	float getRadius() const { return _radius; }

	// Returns the agent's position.
	glm::vec2 getPos() const { return glm::vec2(_x, _y); }

	// Sets the agent's position.
	void setPos(glm::vec2 pos) { _x = pos.x; _y = pos.y; }

	// Returns the agent's centered coordinates.
	glm::vec2 getCentered() const { return _sprite->getCentered(); }

	// Returns whether or not the agent has been initialized.
	bool isInit() const { return _isInit; }

	// Returns whether or not the agent is alive.
	bool isAlive() const { return _alive; }

	// Sets the agent and all its sub-agents and sub-sprites invisible.
	void setInvisible();
	// Sets the agent and all its sub-agents and sub-sprites to be visible.
	void setVisible();
	// Returns whether or not the agent is visible.
	bool isVisible() const { return _visible; }

	// Sets the agent to disabled.
	virtual void disable() { _enabled = false; }
	// Sets the agent to enabled.
	virtual void enable() { _enabled = true; }
	// Returns whether or not the agent is enabled.
	virtual bool isEnabled() { return _enabled; }

	// Processes the agent's current timers. Contains logic for removing the slow effects on agents. Should be called every step.
	void processTimers(float step);

	// Slows the agents and turns on the slow effect for all sub-agents. If the sub-agent doesn't need its slowed effect turned on,
	// then this function should be overridden.
	virtual void slow() { _slowedEffect->setVisible(); _isSlowed = true; _slowTimer = 0; for(auto& a : _subAgents) { a->slow(); } }

	// Allows the current agent's alpha to be set from 0 to 255, 255 being opaque. Sets the alpha of all sub-agents and sub-sprites as well.
	void setAlpha(GLubyte alpha) { _sprite->setAlpha(alpha); for(auto& a : _subAgents) { a->setAlpha(alpha); } for(auto& s : _subSprites) { s->setAlpha(alpha); } }
	// Returns the main sprite's current alpha.
	GLubyte getAlpha() const { return _sprite->getAlpha(); }

protected:
	// Constants used for the slow timer.
	const float SLOW_MULT = 0.5f;
	const float SLOW_TIME = 120.0f;

	float _x, _y, _width, _height, _depth, _rotation, _radius, _speed, _rotationOffset, _slowTimer;
	bool _isInit, _alive, _visible, _enabled, _isSlowed;
	glm::vec2 centerOffset;

	std::vector<Agent*> _subAgents;
	std::vector<GameEngine::Sprite*> _subSprites;
	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::Sprite* _sprite;
	GameEngine::Sprite* _slowedEffect;
	GameEngine::Random* _Random;
	GameEngine::Hitbox _hitbox;
};

