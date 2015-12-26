#pragma once

#include "Agent.h"
#include <GameEngine/Random.h>

class EnemySuper : public Agent
{
public:
	EnemySuper();
	virtual ~EnemySuper();

	float ENEMY_SPEED = 0.025f;

	void init(float x, float y, float width, float height, float depth, int side, 
			  std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager, GameEngine::Random* Random);
	void moveToTarget(float speed);
	virtual void think() {}
	virtual void onCollide() {}
	double getChance(){ return _chance; };

protected:
	float _chance;
	glm::vec2 _target;
	GameEngine::Random* _Random;
	virtual void logicInit(int side) {}
};

