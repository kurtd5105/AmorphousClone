#pragma once
#include "Vertex.h"
#include "ResourceManager.h"
#include <vector>
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

		GLuint getTextureID() const { return _texture.id; }
		float getDepth() const { return _depth; }
		float getRotation() const { return _rotation; }
		Vertex getVertexAt(int i) { return _vertices[i]; }
		glm::vec2 getCentered() const { return glm::vec2(_x, _y) + _center; }
		glm::vec2 getPosition() const { return glm::vec2(_x, _y); }

		void setInvisible() { _visible = false; }
		void setVisible() { _visible = true; }
		bool isVisible() const { return _visible; }

		void setAlpha(GLubyte alpha) { for(auto& v : _vertices) { v.color.a = alpha; } }
		GLubyte getAlpha() const { return _vertices[0].color.a; }

	private:
		glm::vec2 Sprite::rotatePoint(float x, float y, float angle) const;

		std::vector<float> _offset;
		glm::vec2 _center;

		GLTexture _texture;
		float _x, _y, _width, _height, _depth, _rotation;
		bool _visible;
		std::vector<Vertex> _vertices;
	};
}
