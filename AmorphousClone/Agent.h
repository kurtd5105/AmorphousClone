#pragma once

#include <string>

#include <GameEngine/SpriteManager.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/Hitbox.h>
#include <GameEngine/Random.h>

class EnemySuper;
class Goople;

class Player;

class Agent {
public:
	Agent();
	virtual ~Agent();

	virtual void translate(float x, float y, float speed);
	void rotate(float angle);
	void pointAt(glm::vec2 pos);
	void moveTo(Agent* agent, float speed);
	void lockOn(Agent* agent);
	bool collideAgents(Agent *agent);

	virtual void attack();
	virtual void kill();

	float getRotation() { return _sprite->getRotation(); }
	float getRotationOffset() { return _rotationOffset; }
	float getRadius() { return _radius; }
	glm::vec2 getPos() { return glm::vec2(_x, _y); }
	void setPos(glm::vec2 pos) { _x = pos.x; _y = pos.y; }
	glm::vec2 getCentered() { return _sprite->getCentered(); }

	bool isInit() { return _isInit; }

	void setInvisible();
	void setVisible();
	bool isVisible() { return _visible; }

	void disable() { _enabled = false; }
	void enable() { _enabled = true; }
	bool isEnabled() { return _enabled; }

protected:
	float _x, _y, _width, _height, _depth, _rotation, _radius, _speed, _rotationOffset;
	bool _isInit, _visible, _enabled;
	glm::vec2 centerOffset;

	std::vector<Agent*> _subAgents;
	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::Sprite* _sprite;
	GameEngine::Random* _Random;
	GameEngine::Hitbox _hitbox;
};

