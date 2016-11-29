#pragma once
#include "SimpleButton.h"
#include "Text.h"
#include "Vertex.h"

#include <functional>

namespace GameEngine {
	class FontBatcher;
	class SpriteManager;

	class SelectionBox {
	public:
		SelectionBox();
		~SelectionBox();

		void init(float buttonX, float y, float buttonWidth, float buttonHeight, float textWidth, float depth, glm::vec2 scaling, std::vector<std::string> options,
				  std::string nameLeft, std::string nameRight, std::string textLPath, std::string aniLPath, std::string textRPath, std::string aniRPath,
				  Color color, std::function<void(void)> callbackLeft, std::function<void(void)> callbackRight, SpriteManager* manager, FontBatcher* fontBatcher);

		void setSelection(std::string selection);
		void setSelection(unsigned int index);

		void setOptions(std::vector<std::string> options);

		void forward();
		void backward();

		SimpleButton* getLeft() { return &_left; }
		SimpleButton* getRight() { return &_right; }
		unsigned int getIndex() const { return _index; }
		std::vector<std::string> getStrings() const { return _options; }

	private:
		float _leftX, _rightX, _textX, _y, _buttonWidth, _textWidth, _depth;
		unsigned int _count, _index;
		std::vector<std::string> _options;

		SpriteManager* _SpriteManager;
		FontBatcher* _FontBatcher;

		SimpleButton _left, _right;
		Text _text;
		Color _color;
	};
}
