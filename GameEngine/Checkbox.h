#pragma once

#include "Button.h"

namespace GameEngine {
	class Checkbox : public Button {
	public:
		Checkbox();
		~Checkbox();

		void init(float x, float y, float width, float height, float depth, std::string texPath, std::string aniPath,
				  std::string text, Color color, std::function<void(void)> callback, SpriteManager* manager, FontBatcher* fontBatcher);

		std::function<void(void)> onClick();
	private:
		bool _isPushed;
	};
}
