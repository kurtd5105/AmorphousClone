#pragma once

#include "Button.h"

namespace GameEngine {
	class SimpleButton : public Button {
	public:
		SimpleButton();
		~SimpleButton();

		void init(float x, float y, float width, float height, float depth, std::string texPath, std::string aniPath, std::string name, std::function<void(void)> callback, GameEngine::SpriteManager* manager);
	};
}
