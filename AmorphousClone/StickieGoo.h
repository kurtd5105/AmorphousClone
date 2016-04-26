#pragma once
#include "GameEngine/Sprite.h"
#include "GameEngine/SpriteManager.h"

class StickieGoo {
public:
	StickieGoo(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager);
	~StickieGoo();

	void fade(float step);

	const float PERSIST_TIME = 120.0f;
	const float FADE_TIME = 180.0f;

	bool isAlive() const { return _alive; }
	float getRadius() const { return _radius; }
	glm::vec2 getPos() const { return glm::vec2(_x, _y); }
private:
	float _step, _x, _y, _width, _height, _radius, _depth;
	bool _alive;

	GameEngine::Sprite* _sprite;
	GameEngine::SpriteManager* _SpriteManager;
};