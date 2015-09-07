#pragma once

#include <string>

#include <GameEngine/SpriteManager.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/Hitbox.h>

class EnemySuper;
class Goople;

class Player;

class Agent {
public:
	Agent();
	virtual ~Agent();

	virtual void translate(float x, float y);
	void rotate(float angle);
	void pointAt(glm::vec2 pos);

	virtual void attack();
	virtual void kill();

	float getRotation() { return _sprite->getRotation(); }
	glm::vec2 getPos() { return glm::vec2(_x, _y); }
	glm::vec2 getCentered() { return _sprite->getCentered(); }

protected:
	float _x, _y, _width, _height, _depth, _rotation, _radius, _speed;

	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::Sprite* _sprite;
	GameEngine::Hitbox _hitbox;
};

