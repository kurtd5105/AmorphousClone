#include "StickieGoo.h"
#include <GameEngine/Sprite.h>
#include <GameEngine/SpriteInfo.h>
#include <GameEngine/SpriteManager.h>
#include <GameEngine/Errors.h>

StickieGoo::StickieGoo(GameEngine::SpriteInfo* info) : _step(0.0f), _alive(true), _SpriteManager(nullptr) {
	_x = info->x;
	_y = info->y;
	_width = info->width;
	_height = info->height;
	_radius = _width;
	_depth = info->depth;
	_SpriteManager = info->manager;

	// Loads the main sprite into the sprite manager.
	_sprite = _SpriteManager->addSprite(_x, _y, _width, _height, _depth, info->UVmM, info->path);
}

StickieGoo::~StickieGoo() {
	// If the sprite manager exists, then the sprite may need to be deleted.
	if(_SpriteManager != nullptr) {
		// Delete the sprite from the sprite manager if the sprite exists.
		if(_sprite != nullptr) {
			_SpriteManager->deleteSprite(_sprite);
		}
	// If the sprite exists and the sprite manager doesn't, then there was a fatal error and memory will leak!
	} else if(_sprite != nullptr) {
		GameEngine::fatalGenericError("Sprite deletion but no manager to delete with.");
	} else {
		// Optional output for debugging
		//std::cout << "No SpriteManager to delete sprites, but sprites are already deleted." << std::endl;
	}
}

void StickieGoo::fade(float step) {
	_step += step;

	// If the current step is in the fade time then fade it.
	if(_step > PERSIST_TIME && _step - PERSIST_TIME < FADE_TIME) {
		// Set the alpha so it fades from full opaqueness to semi-transparency.
		_sprite->setAlpha(GLubyte((1.0f - ((_step - PERSIST_TIME) / (1.2f * FADE_TIME))) * 255));
	// If the current step is outside of the persist and fade time then make it invisible and not alive.
	} else if(_step > PERSIST_TIME + FADE_TIME) {
		_sprite->setAlpha(0);
		_alive = false;
	}
}
