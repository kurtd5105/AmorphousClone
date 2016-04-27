#pragma once
#include <GameEngine/Random.h>
#include "EnemySuper.h"

// A Goople is a type of enemy. It is meant to be instantiated and used in the main game.
class Goople : public EnemySuper {
public:
	// Initializes the Goople specific necessities. Requires a starting side as well as a random number generator and its dimensions.
	Goople(int side, GameEngine::Random* Random, float width, float height);
	~Goople();
	

	// Runs required logic for the Goople every frame.
	void think() override;

	// Runs any necessary logic if the Goople is killed.
	void onCollide() override;

private:
	// Setup function for determining the target side that the Goople will move towards.
	void logicInit(int side, float width, float height);
	
	int _hp;
	int _damage = 0;

	// A pointer to the random number generator to be used by this enemy for random number generation. Should not be
	// modified by this class or any subclass.
	GameEngine::Random* _Random;
};

