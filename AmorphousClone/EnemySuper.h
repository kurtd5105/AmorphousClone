#pragma once

#include "Agent.h"

class EnemySuper : public Agent
{
public:
	EnemySuper();
	virtual ~EnemySuper();

	float ENEMY_SPEED = 0.025f;

	void init(float x, float y, float width, float height, float depth, int side, 
			  std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager, GameEngine::Random* Random);
	virtual void think() {}
	virtual void onCollide() {}
	double getChance(){ return _chance; };

protected:
	float _chance;

	virtual void logicInit(int side) {}
};

