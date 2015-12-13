#pragma once
#include <string>
#include <glm/glm.hpp>

#include "Font.h"
#include "FontBatcher.h"
#include "Text.h"
#include "Vertex.h"

namespace GameEngine {
	class Text {
	public:
		Text();
		~Text();

		void init(std::string text, glm::vec2 position, glm::vec2 scaling, float depth, Color tint, FontBatcher& batcher);
	private:
		unsigned int _index;
	};
}
