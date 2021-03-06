#pragma once
#include <GameEngine/Random.h>
#include "EnemySuper.h"

class Goople : public EnemySuper {
public:
	Goople(int side, GameEngine::Random* Random, float width, float height);
	~Goople();

	int _damage = 0;

	void think() override;
	void onCollide() override;

private:
	int _hp;
	GameEngine::Random* _Random;
	void logicInit(int side, float width, float height);
};

