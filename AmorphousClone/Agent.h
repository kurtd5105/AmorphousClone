#pragma once

#include <GameEngine/SpriteManager.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/Hitbox.h>
#include <GameEngine/Random.h>

class EnemySuper;
class Goople;
class Stickie;
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
	bool collideAgents(Agent *agent) const;

	virtual void attack(float step);
	virtual void kill();

	float getRotation() const { return _sprite->getRotation(); }
	float getRotationOffset() const { return _rotationOffset; }
	float getRadius() const { return _radius; }
	glm::vec2 getPos() const { return glm::vec2(_x, _y); }
	void setPos(glm::vec2 pos) { _x = pos.x; _y = pos.y; }
	glm::vec2 getCentered() const { return _sprite->getCentered(); }

	bool isInit() const { return _isInit; }
	bool isAlive() const { return _alive; }

	void setInvisible();
	void setVisible();
	bool isVisible() const { return _visible; }

	virtual void disable() { _enabled = false; }
	virtual void enable() { _enabled = true; }
	virtual bool isEnabled() { return _enabled; }

	void processTimers(float step);

	void slow() { _slowedEffect->setVisible(); _isSlowed = true; _slowTimer = 0; }

	void setAlpha(GLubyte alpha) { _sprite->setAlpha(alpha); for(auto& a : _subAgents) { a->setAlpha(alpha); } }
	GLubyte getAlpha() const { return _sprite->getAlpha(); }

protected:
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

