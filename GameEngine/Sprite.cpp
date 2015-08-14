#include "Sprite.h"

namespace GameEngine {
	Sprite::Sprite(float x, float y, float width, float height, float depth, std::string path, ResourceManager* manager) {
		_texture = manager->getTexture(path);
		Vertex vertex;

		//Triangle 1
		//                     x		, y			, r, g, b, a, u   , v

		vertex.setVertex(x + width, y + height, 0, 0, 0, 0, 1.0f, 1.0f);
		_vertices.push_back(vertex);
		//_vertices.emplace_back(x + width, y + height, 0, 0, 0, 0, 1.0f, 1.0f);

		vertex.setVertex(x, y + height, 0, 0, 0, 0, 0.0f, 1.0f);
		_vertices.push_back(vertex);
		//_vertices.emplace_back(x, y + height, 0, 0, 0, 0, 0.0f, 1.0f);

		vertex.setVertex(x, y, 0, 0, 0, 0, 0.0f, 0.0f);
		_vertices.push_back(vertex);
		//_vertices.emplace_back(x, y, 0, 0, 0, 0, 0.0f, 0.0f);

		//Triangle 2
		vertex.setVertex(x, y, 0, 0, 0, 0, 0.0f, 0.0f);
		_vertices.push_back(vertex);
		//_vertices.emplace_back(x, y, 0, 0, 0, 0, 0.0f, 0.0f);

		vertex.setVertex(x + width, y, 0, 0, 0, 0, 1.0f, 0.0f);
		_vertices.push_back(vertex);
		//_vertices.emplace_back(x + width, y, 0, 0, 0, 0, 1.0f, 0.0f);

		vertex.setVertex(x + width, y + height, 0, 0, 0, 0, 1.0f, 1.0f);
		_vertices.push_back(vertex);
		//_vertices.emplace_back(x + width, y + height, 0, 0, 0, 0, 1.0f, 1.0f);
	}

	Sprite::~Sprite() {
	}
}