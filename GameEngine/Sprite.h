#pragma once
#include "Vertex.h"
#include "ResourceManager.h"
#include <vector>
#include <string>
#include <glm\glm.hpp>

namespace GameEngine {
	class Sprite {
	public:
		Sprite();//(float x, float y, float width, float height, float depth, std::string path, ResourceManager* manager);
		~Sprite();
		//																	UVmM: aka UVminMax = {Umin, Umax, Vmin, Vmax}
		void init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, ResourceManager* manager);

		void translate(float x, float y);
		void rotate(float angle);

		GLuint getTextureID() { return _texture.id; }
		float getDepth() { return _depth; }
		float getRotation() { return _rotation; }
		Vertex getVertexAt(int i) { return _vertices[i]; }

	private:
		glm::vec2 Sprite::rotatePoint(float x, float y, float angle);

		GLTexture _texture;
		float _x, _y, _width, _height, _depth, _rotation;
		std::vector<Vertex> _vertices;
	};
}
