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

		void setUVmM(std::vector<float> UVmM);
		void setCenterOffset(std::vector<float> offset) { _offset = offset; }

		void translate(float x, float y);
		void rotate(float angle);
		void pointAt(glm::vec2 pos);

		GLuint getTextureID() { return _texture.id; }
		float getDepth() { return _depth; }
		float getRotation() { return _rotation; }
		Vertex getVertexAt(int i) { return _vertices[i]; }
		glm::vec2 getCentered() { return glm::vec2(_x, _y) + _center; }

		void setInvisible() { _visible = false; }
		void setVisible() { _visible = true; }
		bool isVisible() { return _visible; }

	private:
		glm::vec2 Sprite::rotatePoint(float x, float y, float angle);

		std::vector<float> _offset;
		glm::vec2 _center;

		GLTexture _texture;
		float _x, _y, _width, _height, _depth, _rotation;
		bool _visible;
		std::vector<Vertex> _vertices;
	};
}
