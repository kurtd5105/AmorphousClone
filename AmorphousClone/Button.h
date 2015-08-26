#pragma once
#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteManager.h>
#include <GameEngine/Hitbox.h>

#include "GameState.h"

class Button {
public:
	Button();
	~Button();

	void init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameState onClick, GameEngine::SpriteManager* manager);

	GameState click() { return _onClick; }
	GameEngine::Hitbox* getHitbox() { return &_hitbox; }

private:
	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::Sprite* _sprite;
	GameEngine::Hitbox _hitbox;

	GameState _onClick;
};

