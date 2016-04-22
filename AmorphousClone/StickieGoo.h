#pragma once
#include "EnemySuper.h"

class StickieGoo : public EnemySuper {
public:
	StickieGoo(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager);
	~StickieGoo();

	void fade(float step);
	const float FADE_TIME = 180.0f;
private:
	float _step;
};