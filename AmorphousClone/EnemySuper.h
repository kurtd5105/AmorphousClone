#pragma once
#include "Agent.h"

class StickieGoo;
namespace GameEngine { 
	class Random; 
	class SpriteInfo;
}

// An enum designed to make identifying the subclass of enemy.
enum EnemyType { GOOPLE, STICKIE };

// Defines required capabilities of all enemies. It is not meant to be instantiated.
class EnemySuper : public Agent
{
public:
	// Initializes some values to their defaults.
	EnemySuper();
	virtual ~EnemySuper();

	// Initializes the enemy. Performs all necessary setup for use including setting local variables, and loading the necessary
	// Sprites. Assumes the enemy shape is a circle.
	virtual void init(GameEngine::SpriteInfo* info, int side, std::string slowFx, GameEngine::Random* Random);


	// Moves the enemy towards a point target in a discrete step of the locally set speed and the passed speed argument. The speed
	// argument DOES NOT control the speed of the movement, it is a multiplier.
	void moveToTarget(float speed);

	// Allows the target to be set as a point on the screen.
	void setTarget(glm::vec2 target) { _target = target; };

	// Returns the enemy's current target.
	glm::vec2 getTarget() const { return _target; };


	// Function to be called to allow the object to execute logic. To be overridden by an enemy subclass.
	virtual void think() {}

	// Function to be called on collision if additional collision logic is needed. To be overridden by an enemy subclass.
	virtual void onCollide() {}

	// Getter for the enemy's chance, not currently useful.
	// TODO: figure out if this is necessary to store.
	double getChance() const { return _chance; };

	
	// Allows the enemy to be excluded from other collisions if it has already collided.
	void setCollided(bool collided) { _collided = collided; };

	// Returns whether or not the enemy has collided and this collision is preventing it from colliding further.
	bool getCollided() const { return _collided; };


	// Allows for control of whether or not the enemy will be able to move towards its target, or perform other logic that
	// modifies its state.
	void enable() override { _enabled = true; }

	// Sets the enemy as disabled.
	void disable() override { _enabled = false; }

	// Returns whether or not the enemy is enabled.
	bool isEnabled() override { return _enabled; };


	// Returns the enemy type, which is set by the enemy subclass. This will fail if EnemySuper is instantiated, as it
	// is not initialized by EnemySuper.
	EnemyType getType() const { return _type; }


	// Returns a reference to goo that this enemy has spawned, if it has at all. If there is no goo that has been dropped
	// then nullptr will be returned. If there is goo, it is expected for the owner of the enemy to keep track of the
	// goo, unless it will be keeping track of the enemy.
	// TODO: use smart pointers to make sure the goo is deleted when no longer in use.
	StickieGoo* getGoo() const { return _goo; }

	// Returns whether or not it has goo or will spawn goo. It does not make a distinction between if it currently has
	// or will spawn goo, to find out call getGoo().
	bool hasGoo() const { return _hasGoo; }


	// Disables the enemy, makes it invisible and spawns goo if the enemy spawns goo.
	void kill() override;


	//Global Variables
	float ENEMY_SPEED = 2.0f;

protected:
	// Setup function that can be called by an enemy subclass once the enemy is initialized. It will be called in init().
	virtual void logicInit(int side) {}
	
	float _chance;
	bool _collided, _hasGoo;

	EnemyType _type;
	StickieGoo* _goo;

	glm::vec2 _target;

	// A pointer to the random number generator to be used by this enemy for random number generation. Should not be
	// modified by this class or any subclass.
	GameEngine::Random* _Random;
};

