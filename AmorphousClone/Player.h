#pragma once
#include "Agent.h"
#include "Sword.h"
#include "EnemySuper.h"

namespace GameEngine { class SpriteManager; }

// The Player is the person that the player plays as. It is meant to be instantiated and used in the main game.
class Player : public Agent {
public:
	// Initializes some values to their defaults.
	Player();
	~Player();

	// Initializes the Player. Performs all necessary setup for use including setting local variables, and loading the necessary
	// Sprites. Assumes the player shape is a circle.
	void init(float x, float y, float width, float height, float depth, glm::vec2 scalingFactors, std::vector<float> UVmM,
			  std::string path, std::string slowFx, GameEngine::SpriteManager* manager);


	// Function to be called on collision in order to deflect the player and start the knockback.
	void onCollide(EnemyType type, float targetRotation);
	

	// Returns whether or not the player is in the knockback effect.
	bool isKnockback() const { return _knockback; }

	// Returns whether or not the player is invincible and immune to further effects such as knockback, damaged and slowing.
	bool isInvincible() const { return _invincible; }


	// Returns a pointer to the player's sword. The caller is to not delete the sword after use.
	Sword* getSword() { return &_sword; }


	// Function to call if the player is being knocked back. Takes a timestep and will possibly remove the knockback effect after called.
	void knockback(float step);

	// Player speed constant.
	const float PLAYER_SPEED = 4.0f;

private:
	// The speed that the player gets knocked back at.
	const float KNOCKBACK_SPEED = 0.5f;
	// The amount of time the player gets knocked back for.
	const float KNOCKBACK_TIME = 60.0f;
	// The amount of time the player is invincible for after being knocked back.
	const float INVULNERABLE_TIME = 30.0f;


	bool _knockback, _invincible;
	float _step, _prevStep, _targetRotation;
	int _gloopleBumps;


	// The player's sword.
	Sword _sword;
	
};
