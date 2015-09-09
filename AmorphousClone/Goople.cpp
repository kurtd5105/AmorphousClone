#include "Goople.h"


Goople::Goople()
{
}


Goople::~Goople()
{
}


void Goople::init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_depth = depth;
	_radius = width / 2;
	_speed = GOOPLE_SPEED;
	_SpriteManager = manager;
	//Assumes player is a circle
	_sprite = _SpriteManager->addSprite(x, y, width, height, depth, UVmM, path);
	_hitbox.init(x, y, width, height, _radius);
}
