#pragma once
#include "Hitbox.h"
#include "SpriteSheet.h"
#include "Text.h"

#include <functional>

namespace GameEngine {
	class FontBatcher;
	class InputManager;
	class Sprite;
	class SpriteManager;

	class Button {
	public:
		Button();
		virtual ~Button();

		virtual std::function<void(void)> onClick() { return _callback; };
		virtual void onIdle();
		virtual void onHover();
		virtual void onPush();
		Hitbox* getHitbox() { return &_hitbox; }

	protected:
		std::function<void(void)> _callback;

		SpriteSheet _sheet;
		SpriteManager* _SpriteManager;
		FontBatcher* _FontBatcher;
		InputManager* _InputManager;

		Sprite* _sprite;
		Text _text;
		Color _color;
		Hitbox _hitbox;

		std::string _name;

		bool _isPushed;
	};
}
