#pragma once
#include <functional>

#include "Hitbox.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "SpriteSheet.h"

namespace GameEngine {
	class Button {
	public:
		Button();
		~Button();

		void init(float x, float y, float width, float height, float depth, std::string texPath, std::string aniPath, std::string name, std::function<void(void)> callback, GameEngine::SpriteManager* manager);

		std::function<void(void)> onClick() { return _callback; };
		Hitbox* getHitbox() { return &_hitbox; }

	private:
		std::function<void(void)> _callback;

		SpriteSheet _sheet;
		SpriteManager* _SpriteManager;
		Sprite* _sprite;
		Hitbox _hitbox;

		std::string _name;
	};
}
