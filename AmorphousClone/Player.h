#pragma once
#include "Agent.h"
#include "Sword.h"
#include "EnemySuper.h"

class Player : public Agent {
public:
	Player();
	~Player();

	const float PLAYER_SPEED = 4.0f;

	void init(float x, float y, float width, float height, float depth, glm::vec2 scalingFactors, std::vector<float> UVmM,
			  std::string path, std::string slowFx, GameEngine::SpriteManager* manager);
	void onCollide(EnemyType type, float targetRotation);
	
	bool isKnockback() const { return _knockback; }
	bool isInvincible() const { return _invincible; }
	Sword* getSword() { return &_sword; }

	void knockback(float step);

private:
	const float KNOCKBACK_SPEED = 0.5f;
	const float KNOCKBACK_TIME = 60.0f;
	const float INVULNERABLE_TIME = 30.0f;
	Sword _sword;
	bool _knockback, _invincible;
	float _step, _prevStep, _targetRotation;
	int _gloopleBumps;
};
