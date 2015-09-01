#define _USE_MATH_DEFINES
#include "Sprite.h"
#include <math.h>
#include <iostream>

namespace GameEngine {
	Sprite::Sprite() : _x(0.0f), _y(0.0f), _width(0.0f), _height(0.0f), _depth(0.0f), _rotation(0.0f) {}
		
	void Sprite::init(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, ResourceManager* manager) {
		_texture = manager->getTexture(path);
		_x = x; _y = y; _width = width; _height = height; _depth = depth;
		Vertex vertex;

		//If the UV parameter was passed as empty or incomplete, default to full sprite
		if(UVmM.size() != 4) {
			UVmM = std::vector<float>{0.0f, 1.0f, 0.0f, 1.0f};
		}
		
		//                     x		, y			, r, g, b, a, u   , v
		
		//Triangle 1
		//Top right [0]
		vertex.setVertex(x + width, y + height, 0, 0, 0, 0, UVmM[1], UVmM[3]);
		_vertices.push_back(vertex);

		//Top left [1]
		vertex.setVertex(x, y + height, 0, 0, 0, 0, UVmM[0], UVmM[3]);
		_vertices.push_back(vertex);

		//Bottom left [2]
		vertex.setVertex(x, y, 0, 0, 0, 0, UVmM[0], UVmM[2]);
		_vertices.push_back(vertex);

		//Triangle 2
		//Bottom left [3] = [2]
		vertex.setVertex(x, y, 0, 0, 0, 0, UVmM[0], UVmM[2]);
		_vertices.push_back(vertex);

		//Bottom right [4]
		vertex.setVertex(x + width, y, 0, 0, 0, 0, UVmM[1], UVmM[2]);
		_vertices.push_back(vertex);

		//Top right [5] = [0]
		vertex.setVertex(x + width, y + height, 0, 0, 0, 0, UVmM[1], UVmM[3]);
		_vertices.push_back(vertex);

		_center = glm::vec2(_width / 2.0f, _height / 2.0f);
	}

	Sprite::~Sprite() {
	}

	void Sprite::translate(float x, float y) {
		_x += x;
		_y += y;
		_vertices[0].setPosition(_vertices[0].position.x + x, _vertices[0].position.y + y);
		_vertices[1].setPosition(_vertices[1].position.x + x, _vertices[1].position.y + y);
		_vertices[2].setPosition(_vertices[2].position.x + x, _vertices[2].position.y + y);
		_vertices[3].setPosition(_vertices[3].position.x + x, _vertices[3].position.y + y);
		_vertices[4].setPosition(_vertices[4].position.x + x, _vertices[4].position.y + y);
		_vertices[5].setPosition(_vertices[5].position.x + x, _vertices[5].position.y + y);
	}

	void Sprite::rotate(float angle) {
		_rotation = angle;

		//Center the sprite around the origin
		glm::vec2 topLeft(-_center.x, _center.y);
		glm::vec2 bottomLeft(-_center.x, -_center.y);
		glm::vec2 bottomRight(_center.x, -_center.y);
		glm::vec2 topRight(_center.x, _center.y);

		//Rotate the sprite around the origin
		topLeft = rotatePoint(topLeft.x, topRight.y, _rotation) + _center;
		bottomLeft = rotatePoint(bottomLeft.x, bottomLeft.y, _rotation) + _center;
		bottomRight = rotatePoint(bottomRight.x, bottomRight.y, _rotation) + _center;
		topRight = rotatePoint(topRight.x, topRight.y, _rotation) + _center;

		//Triangle 1
		//Top right
		_vertices[0].setPosition(_x + topRight.x, _y + topRight.y);

		//Top left
		_vertices[1].setPosition(_x + topLeft.x, _y + topLeft.y);

		//Bottom left
		_vertices[2].setPosition(_x + bottomLeft.x, _y + bottomLeft.y);

		//Triangle 2
		//Bottom left
		_vertices[3].setPosition(_x + bottomLeft.x, _y + bottomLeft.y);

		//Bottom right
		_vertices[4].setPosition(_x + bottomRight.x, _y + bottomRight.y);

		//Top right
		_vertices[5].setPosition(_x + topRight.x, _y + topRight.y);
	}

	void Sprite::pointAt(glm::vec2 pos) {
		//Subtract the position from the center position
		glm::vec2 diff(pos - (glm::vec2(_x, _y) + glm::vec2(_width / 2)));
		//If the mouse isn't directly on the center then normalize the difference and rotate the sprite
		if(diff.x != 0 || diff.y != 0) {
			pos = glm::normalize(diff);
			//Rotate it based on the arc cos of the x position and flip it if the y position is greater than 0
			rotate(acos(pos.x) * (pos.y < 0.0f ? 1.0f : -1.0f));// - (M_PI/2)); //rotates player.png to face the mouse on the arrow guide
		}
	}
	
	glm::vec2 Sprite::rotatePoint(float x, float y, float angle) {
		glm::vec2 r;
		//Apply rotation matrix
		r.x = x * cos(angle) - y * sin(angle);
		r.y = x * sin(angle) + y * cos(angle);
		return r;
	}
}