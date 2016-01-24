#include "Button.h"

namespace GameEngine {
	Button::Button() {
	}


	Button::~Button() {
	}

	void Button::init(float x, float y, float width, float height, float depth, std::string texPath, std::string aniPath, std::string name, std::function<void(void)> callback, GameEngine::SpriteManager* manager) {
		_name = name;
		_callback = callback;
		_SpriteManager = manager;
		_sprite = _SpriteManager->addSprite(x, y, width, height, depth, std::vector<float>{}, texPath);
		_sheet.init(aniPath, _sprite, _SpriteManager->getResourceManager());
		_sheet.setAnim(_name + "IDLE");
		_hitbox.init(x, y, width, height, 0);
	}
}
