#pragma once
#include "GameEngine/Sprite.h"
#include "GameEngine/SpriteManager.h"

// StickieGoo is the goo that is dropped by a Stickie on death. Should only be instantiated by a Stickie.
class StickieGoo {
public:
	// Constructor that creates the goo and loads the goo sprite.
	StickieGoo(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager);
	~StickieGoo();


	// Used to fade the goo and eventually make it disappear. Should be called when the goo is dropped.
	void fade(float step);


	// Returns whether or not the goo is active or not.
	bool isAlive() const { return _alive; }


	// Returns the radius of the goo.
	float getRadius() const { return _radius; }


	// Returns the position of the goo.
	glm::vec2 getPos() const { return glm::vec2(_x, _y); }


	// Public constants used for timing the goo fading.
	const float PERSIST_TIME = 120.0f;
	const float FADE_TIME = 180.0f;
private:
	float _step, _x, _y, _width, _height, _radius, _depth;
	bool _alive;

	GameEngine::Sprite* _sprite;
	GameEngine::SpriteManager* _SpriteManager;
};