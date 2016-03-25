#pragma once
//#include <GameEngine/Hitbox.h>
//#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteManager.h>
#include "Agent.h"

class Sword : public Agent {
public:
	Sword();
	~Sword();

	void init(float x, float y, float angle, GameEngine::SpriteManager* manager);

	void attack() override;//needs some sort of timer integrated

//private:
	/*float _x, _y, _rotation;

	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::Sprite* _sprite;
	GameEngine::Hitbox _hitbox;*/
};

