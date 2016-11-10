#pragma once

#include "Agent.h"
#include <GameEngine/Random.h>
#include "StickieGoo.h"


enum EnemyType { GOOPLE, STICKIE };

class EnemySuper : public Agent
{
public:
	EnemySuper();
	virtual ~EnemySuper();

	float ENEMY_SPEED = 2.0f;


	virtual void init(float x, float y, float width, float height, float depth, int side, std::vector<float> UVmM, std::string path,
					  std::string slowFx, GameEngine::SpriteManager* manager, GameEngine::Random* Random);
	void moveToTarget(float speed);
	virtual void think() {}
	virtual void onCollide() {}
	double getChance() const { return _chance; };

	void setTarget(glm::vec2 target) { _target = target; };
	glm::vec2 getTarget() const { return _target; };

	void setCollided(bool collided) { _collided = collided; };
	bool getCollided() const { return _collided; };

	void enable() override { _enabled = true; }
	void disable() override { _enabled = false; }
	bool isEnabled() override { return _enabled; };

	EnemyType getType() const { return _type; }

	StickieGoo* getGoo() const { return _goo; }
	bool hasGoo() const { return _hasGoo; }

	void kill() override;

protected:
	virtual void logicInit(int side) {}
	
	float _chance;
	bool _collided, _hasGoo;

	glm::vec2 _target;
	GameEngine::Random* _Random;
	StickieGoo* _goo;
	
	EnemyType _type;
};

