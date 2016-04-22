#pragma once
#include <GameEngine/Random.h>
#include "EnemySuper.h"

class Stickie : public EnemySuper {
public:
	Stickie(int side, GameEngine::Random* Random, float width, float height);
	~Stickie();

	int _damage = 0;

	void think() override;
	void onCollide() override;

private:
	void logicInit(int side, float width, float height);
	
	int _hp;

	GameEngine::Random* _Random;
};
