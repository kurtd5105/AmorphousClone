#include "Checkbox.h"

namespace GameEngine {
	Checkbox::Checkbox() : _isPushed(false) {
	}


	Checkbox::~Checkbox() {
	}

	void Checkbox::init(float x, float y, float width, float height, float depth, std::string texPath, std::string aniPath,
						std::string text, Color color, std::function<void(void)> callback, SpriteManager* manager, FontBatcher* fontBatcher) {
		_callback = callback;
		_SpriteManager = manager;
		_FontBatcher = fontBatcher;
		_sprite = _SpriteManager->addSprite(x, y, width, height, depth, std::vector<float>{}, texPath);
		_sheet.init(aniPath, _sprite, _SpriteManager->getResourceManager());
		_sheet.setAnim("OFFIDLE");
		_hitbox.init(x, y, width, height, 0);
		_color = color;
		_text.init(text, glm::vec2(x + width, y), glm::vec2(1, 1), 1.0f, _color, _FontBatcher);
	}

	std::function<void(void)> Checkbox::onClick() {
		if(_isPushed) {
			_isPushed = false;
			_sheet.setAnim("OFFIDLE");
		} else {
			_isPushed = true;
			_sheet.setAnim("ONIDLE");
		}
		
		return _callback;
	}
}
