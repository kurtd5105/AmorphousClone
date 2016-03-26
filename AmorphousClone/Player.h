#pragma once
#include "Agent.h"
#include "Sword.h"
#include "EnemySuper.h"

class Player : public Agent {
public:
	Player();
	~Player();

	const float PLAYER_SPEED = 4.0f;

	void init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager);
	void onCollide(EnemyType type);
	
	bool isAlive() const { return _isAlive; }

private:
	Sword _sword;
	bool _isAlive;
	int _gloopleBumps;
};
