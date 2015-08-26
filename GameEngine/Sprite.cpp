#include "Sprite.h"

namespace GameEngine {
	Sprite::Sprite() : _x(0), _y(0), _width(0), _height(0), _depth(0) {}
		
	void Sprite::init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, ResourceManager* manager) {
		_texture = manager->getTexture(path);
		_x = x; _y = y; _width = width; _height = height; _depth = depth;
		Vertex vertex;

		//If the UV parameter was passed as empty or incomplete, default to full sprite
		if(UVmM.size() != 4) {
			UVmM = std::vector<float>{0.0f, 1.0f, 0.0f, 1.0f};
		}
		//Triangle 1
		//                     x		, y			, r, g, b, a, u   , v

		vertex.setVertex(x + width, y + height, 0, 0, 0, 0, UVmM[1], UVmM[3]);
		_vertices.push_back(vertex);

		vertex.setVertex(x, y + height, 0, 0, 0, 0, UVmM[0], UVmM[3]);
		_vertices.push_back(vertex);

		vertex.setVertex(x, y, 0, 0, 0, 0, UVmM[0], UVmM[2]);
		_vertices.push_back(vertex);

		//Triangle 2
		vertex.setVertex(x, y, 0, 0, 0, 0, UVmM[0], UVmM[2]);
		_vertices.push_back(vertex);

		vertex.setVertex(x + width, y, 0, 0, 0, 0, UVmM[1], UVmM[2]);
		_vertices.push_back(vertex);

		vertex.setVertex(x + width, y + height, 0, 0, 0, 0, UVmM[1], UVmM[3]);
		_vertices.push_back(vertex);
	}

	Sprite::~Sprite() {
	}

	void Sprite::translate(float x, float y) {
		_x += x;
		_y += y;
		_vertices[0].setPosition(_x + _width, _y + _height);
		_vertices[1].setPosition(_x, _y + _height);
		_vertices[2].setPosition(_x, _y);
		_vertices[3].setPosition(_x, _y);
		_vertices[4].setPosition(_x + _width, _y);
		_vertices[5].setPosition(_x + _width, _y + _height);
	}
}