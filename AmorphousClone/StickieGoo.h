#pragma once
#include "GameEngine/Sprite.h"
#include "GameEngine/SpriteManager.h"

class StickieGoo {
public:
	StickieGoo(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager);
	~StickieGoo();

	void fade(float step);
	const float FADE_TIME = 180.0f;

	bool isAlive() const { return _alive; }
private:
	float _step, _x, _y, _width, _height, _depth;
	bool _alive;

	GameEngine::Sprite* _sprite;
	GameEngine::SpriteManager* _SpriteManager;
};