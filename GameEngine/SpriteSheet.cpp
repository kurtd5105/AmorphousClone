#include "SpriteSheet.h"

namespace GameEngine {
	SpriteSheet::SpriteSheet() : _set(0), _step(0), _sprite(nullptr), _ResourceManager(nullptr) {
	}


	SpriteSheet::~SpriteSheet() {
	}

	void SpriteSheet::init(std::string path, Sprite* sprite, ResourceManager* manager) {
		_ResourceManager = manager;
		_sprite = sprite;
		_animation = _ResourceManager->getAnimation(path);
	}

	void SpriteSheet::nextStep() {
		_step++;
		if(_step > _animation.getAnimSize(_set)) {
			_step = 0;
		}
		//Set the sprite UVmM to the correct sprite in the sprite sheet
		_sprite->setUVmM(*_animation.getUVSet(_set, _step));
	}

	void SpriteSheet::setAnim(std::string animName) {
		_set = _animation.getUVLocation(animName);
		_step = 0;
		_sprite->setUVmM(*_animation.getUVSet(_set, _step));
	}

}