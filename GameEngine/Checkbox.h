#pragma once

#include "Button.h"

namespace GameEngine {
	class Checkbox : public Button {
	public:
		Checkbox();
		~Checkbox();

		void init(float x, float y, float width, float height, float depth, glm::vec2 scaling, std::string texPath, std::string aniPath,
				  std::string text, Color color, std::function<void(void)> callback, SpriteManager* manager, FontBatcher* fontBatcher);

		std::function<void(void)> onClick() override;
		bool isPushed() const { return _isPushed; }
	};
}
