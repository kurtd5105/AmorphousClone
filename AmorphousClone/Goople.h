#pragma once
#include "EnemySuper.h"

class Goople : public EnemySuper {
public:
	Goople();
	~Goople();

	const float GOOPLE_SPEED = 0.025f;

	void init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager);

private:

};
