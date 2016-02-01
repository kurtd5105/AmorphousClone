#include "Checkbox.h"

namespace GameEngine {
	Checkbox::Checkbox() {
	}


	Checkbox::~Checkbox() {
	}

	void Checkbox::init(float x, float y, float width, float height, float depth, std::string texPath, std::string aniPath,
						std::string text, Color color, std::function<void(void)> callback, SpriteManager* manager, FontBatcher* fontBatcher) {
		_name = "OFF";
		_callback = callback;
		_SpriteManager = manager;
		_FontBatcher = fontBatcher;

		_color = color;

		_sprite = _SpriteManager->addSprite(x, y, width, height, depth, std::vector<float>{}, texPath);
		_hitbox.init(x, y, width, height, 0);

		_sheet.init(aniPath, _sprite, _SpriteManager->getResourceManager());
		_sheet.setAnim("OFFIDLE");
		
		_text.init(text, glm::vec2(x + width, y), glm::vec2(1, 1), 1.0f, _color, _FontBatcher);
	}

	std::function<void(void)> Checkbox::onClick() {
		//Toggle the button between unchecked and checked
		if(_isPushed) {
			_isPushed = false;
			_name = "OFF";
			_sheet.setAnim("OFFIDLE");
		} else {
			_isPushed = true;
			_name = "ON";
			_sheet.setAnim("ONIDLE");
		}
		
		//Also return the callback when it gets clicked
		return _callback;
	}
}
