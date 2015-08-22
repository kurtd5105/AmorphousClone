#pragma once
#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteManager.h>

#include "GameState.h"

class Button {
public:
	Button();
	~Button();

	void init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameState onClick, GameEngine::SpriteManager* manager);

private:
	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::Sprite* _sprite;

	GameState _onClick;
};

