#pragma once
#include <GameEngine/Random.h>
#include "EnemySuper.h"
#include "StickieGoo.h"

class Stickie : public EnemySuper {
public:
	Stickie(int side, GameEngine::Random* Random, float width, float height);
	~Stickie();

	int _damage = 0;

	void think() override;
	void onCollide() override;
	void kill() override;

private:
	void logicInit(int side, float width, float height);
	
	int _hp;

	GameEngine::Random* _Random;
};
