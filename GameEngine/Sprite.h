#pragma once
#include "Vertex.h"
#include "ResourceManager.h"
#include <vector>
#include <string>

namespace GameEngine {
	class Sprite {
	public:
		Sprite();//(float x, float y, float width, float height, float depth, std::string path, ResourceManager* manager);
		~Sprite();
		//																	UVmM: aka UVminMax = {Umin, Umax, Vmin, Vmax}
		void init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, ResourceManager* manager);
		GLuint getTextureID() { return _texture.id; }
		float getDepth() { return _depth; }
		Vertex getVertexAt(int i) { return _vertices[i]; }

	private:
		GLTexture _texture;
		float _x, _y, _width, _height, _depth;
		std::vector<Vertex> _vertices;
	};
}
