#pragma once
#include "Agent.h"

class Player : public Agent {
public:
	Player();
	~Player();

	const float PLAYER_SPEED = 0.05f;

	void init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager);

private:

};

