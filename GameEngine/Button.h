#pragma once
#include <functional>

#include "Hitbox.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "SpriteSheet.h"

class SimpleButton;

namespace GameEngine {
	class Button {
	public:
		Button();
		~Button();

		std::function<void(void)> onClick() { return _callback; };
		Hitbox* getHitbox() { return &_hitbox; }

	protected:
		std::function<void(void)> _callback;

		SpriteSheet _sheet;
		SpriteManager* _SpriteManager;
		Sprite* _sprite;
		Hitbox _hitbox;

		std::string _name;
	};
}
