#include "StickieGoo.h"

StickieGoo::StickieGoo(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameEngine::SpriteManager* manager) : 
_step(0.0f), _alive(true), _SpriteManager(nullptr) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_radius = _width;
	_depth = depth;
	_SpriteManager = manager;
	_sprite = _SpriteManager->addSprite(x, y, width, height, depth, UVmM, path);
}

StickieGoo::~StickieGoo() {
}

void StickieGoo::fade(float step) {
	_step += step;
	if(_step < FADE_TIME) {
		_sprite->setAlpha((1.0f - (_step/FADE_TIME)) * 255);
	} else {
		_sprite->setAlpha(0);
		_alive = false;
	}
}
