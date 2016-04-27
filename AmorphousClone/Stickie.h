#pragma once
#include <GameEngine/Random.h>
#include "EnemySuper.h"

// A Stickie is a type of enemy. It is meant to be instantiated and used in the main game.
class Stickie : public EnemySuper {
public:
	// Initializes the Stickie specific necessities. Requires a starting side as well as a random number generator and its dimensions.
	Stickie(int side, GameEngine::Random* Random, float width, float height);
	~Stickie();

	
	// Runs required logic for the Stickie every frame.
	void think() override;

	// Runs any necessary logic if the Stickie is killed.
	void onCollide() override;

private:
	void logicInit(int side, float width, float height);
	
	int _hp;
	int _damage = 0;

	// A pointer to the random number generator to be used by this enemy for random number generation. Should not be
	// modified by this class or any subclass.
	GameEngine::Random* _Random;
};
