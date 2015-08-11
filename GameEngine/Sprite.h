#pragma once
#include "Vertex.h"
#include <vector>
#include <string>

namespace GameEngine {
	class Sprite {
	public:
		Sprite(float x, float y, float width, float height, float depth, std::string path);
		~Sprite();


		GLuint getTextureID() { return _textureID; }
		float getDepth() { return _depth; }
		Vertex getVertexAt(int i) { return _vertices[i]; }

	private:
		GLuint _textureID;
		float _depth;
		std::vector<Vertex> _vertices;
	};
}
