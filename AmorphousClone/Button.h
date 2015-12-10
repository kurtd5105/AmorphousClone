#pragma once
#include <GameEngine/Hitbox.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteManager.h>
#include <GameEngine/SpriteSheet.h>

#include "GameState.h"

class Button {
public:
	Button();
	~Button();

	void init(float x, float y, float width, float height, float depth, std::string texPath, std::string aniPath, std::string name, GameState onClick, GameEngine::SpriteManager* manager);

	GameState click() { return _onClick; }
	GameEngine::Hitbox* getHitbox() { return &_hitbox; }

private:
	GameEngine::SpriteSheet _sheet;
	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::Sprite* _sprite;
	GameEngine::Hitbox _hitbox;

	std::string _name;

	GameState _onClick;
};

