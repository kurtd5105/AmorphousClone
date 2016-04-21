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
	void kill() override;

private:
	int _hp;
	GameEngine::Random* _Random;
	void logicInit(int side, float width, float height);
};
