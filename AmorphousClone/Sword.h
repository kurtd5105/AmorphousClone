#pragma once
//#include <GameEngine/Hitbox.h>
//#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteManager.h>
#include "Agent.h"

class Sword : public Agent {
public:
	Sword();
	~Sword();

	void init(float x, float y, float angle, glm::vec2 scalingFactors, GameEngine::SpriteManager* manager);

	void attack(float step) override;//needs some sort of timer integrated

	bool isActive() const { return _isActive; }
	void setActive() { _isActive = true; }

	void slow() override { _isSlowed = true; _slowTimer = 0; };

private:
	float _step;
	const float ATTACK_HALF = float(M_PI) / 30.0f;
	const float ATTACK_HALF_TIME = 30.0f;
	bool _isActive;
	/*float _x, _y, _rotation;

	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::Sprite* _sprite;
	GameEngine::Hitbox _hitbox;*/
};

