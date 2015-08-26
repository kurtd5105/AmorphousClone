#include "Button.h"


Button::Button() {
}


Button::~Button() {
}

void Button::init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, GameState onClick, GameEngine::SpriteManager* manager) {
	_onClick = onClick;
	_SpriteManager = manager;
	_sprite = _SpriteManager->addSprite(x, y, width, height, depth, UVmM, path);
	_hitbox.init(x, y, width, height, 0);
}