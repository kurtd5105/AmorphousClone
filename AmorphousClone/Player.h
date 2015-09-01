#pragma once
#include <string>

#include <GameEngine/SpriteManager.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/Hitbox.h>

class Player {
public:
	Player();
	~Player();

	const float PLAYER_SPEED = 0.05f;

	void init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager);
	
	void translate(float x, float y);
	void rotate(float angle);
	void pointAt(glm::vec2 pos);

	void attack();
	void kill();

	float getRotation() { return _sprite->getRotation(); }

private:
	float _x, _y, _width, _height, _depth, _rotation, _radius;

	GameEngine::SpriteManager* _SpriteManager;
	GameEngine::Sprite* _sprite;
	GameEngine::Hitbox _hitbox;
};

