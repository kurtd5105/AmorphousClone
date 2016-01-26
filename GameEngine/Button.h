#pragma once
#include <functional>

#include "FontBatcher.h"
#include "Hitbox.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "SpriteSheet.h"
#include "Text.h"
#include "Vertex.h"

class SimpleButton;

namespace GameEngine {
	class Button {
	public:
		Button();
		~Button();

		virtual std::function<void(void)> onClick() { return _callback; };
		void onHover();
		void onPush();
		Hitbox* getHitbox() { return &_hitbox; }

	protected:
		std::function<void(void)> _callback;

		SpriteSheet _sheet;
		SpriteManager* _SpriteManager;
		FontBatcher* _FontBatcher;

		Sprite* _sprite;
		Text _text;
		Color _color;
		Hitbox _hitbox;

		std::string _name;
	};
}
