#pragma once
#include <string>
#include <glm/glm.hpp>

#include "FontBatcher.h"
#include "Vertex.h"

namespace GameEngine {
	class Text {
	public:
		Text();
		~Text();

		void init(std::string text, glm::vec2 position, glm::vec2 scaling, float depth, Color tint, FontBatcher* batcher);
		void display();
		void clear() const;
		void changeText(std::string text);
	private:
		bool _used;
		unsigned int _index, _length;
		std::string _text; 
		glm::vec2 _position, _scaling; 
		float _depth; 
		Color _tint;
		FontBatcher* _batcher;
	};
}
