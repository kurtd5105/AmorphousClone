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
		vertex.setVertex(x + width, y + height, 255, 255, 255, 255, UVmM[1], UVmM[3]);
		_vertices.push_back(vertex);

		//Top left [1]
		vertex.setVertex(x, y + height, 255, 255, 255, 255, UVmM[0], UVmM[3]);
		_vertices.push_back(vertex);

		//Bottom left [2]
		vertex.setVertex(x, y, 255, 255, 255, 255, UVmM[0], UVmM[2]);
		_vertices.push_back(vertex);

		//Triangle 2
		//Bottom left [3] = [2]

		//Bottom right [4]
		vertex.setVertex(x + width, y, 255, 255, 255, 255, UVmM[1], UVmM[2]);
		_vertices.push_back(vertex);

		//Top right [5] = [0]
		_center = glm::vec2(_width / 2.0f, _height / 2.0f);
		_offset = std::vector<float>{0.0f, 0.0f};
	}

	Sprite::~Sprite() {
	}

	void Sprite::setUVmM(std::vector<float> UVmM) {
		_vertices[0].setUV(UVmM[1], UVmM[3]);
		_vertices[1].setUV(UVmM[0], UVmM[3]);
		_vertices[2].setUV(UVmM[0], UVmM[2]);
		_vertices[3].setUV(UVmM[1], UVmM[2]);
	}

	void Sprite::translate(float x, float y) {
		_x += x;
		_y += y;
		_vertices[0].setPosition(_vertices[0].position.x + x, _vertices[0].position.y + y);
		_vertices[1].setPosition(_vertices[1].position.x + x, _vertices[1].position.y + y);
		_vertices[2].setPosition(_vertices[2].position.x + x, _vertices[2].position.y + y);
		_vertices[3].setPosition(_vertices[3].position.x + x, _vertices[3].position.y + y);
	}

	void Sprite::rotate(float angle) {
		_rotation = angle;
		glm::vec2 topLeft(-_center.x, _center.y);
		glm::vec2 bottomLeft(-_center.x, -_center.y);
		glm::vec2 bottomRight(_center.x, -_center.y);
		glm::vec2 topRight(_center.x, _center.y);

		glm::vec2 xShift(0.0f, 0.0f);
		glm::vec2 yShift(0.0f, 0.0f);
		//Shift the sprite by its offset from the center of the unit circle based on some multiplier
		//Effect essentially is the same as rotating it around an offset point
		if(_offset[0] != 0.0f) {
			xShift.x = cos(_rotation) * _center.x * _offset[0];
			xShift.y = sin(_rotation) * _center.x * _offset[0];
		}
		if(_offset[1] != 0.0f) {
			yShift.x = cos(_rotation) * _center.y * _offset[1];
			yShift.y = sin(_rotation) * _center.y * _offset[1];
		}
		//Rotate the sprite around the origin
		topLeft = rotatePoint(topLeft.x, topRight.y, _rotation) + _center + xShift + yShift;
		bottomLeft = rotatePoint(bottomLeft.x, bottomLeft.y, _rotation) + _center + xShift + yShift;
		bottomRight = rotatePoint(bottomRight.x, bottomRight.y, _rotation) + _center + xShift + yShift;
		topRight = rotatePoint(topRight.x, topRight.y, _rotation) + _center + xShift + yShift;

		//Triangle 1
		//Top right
		_vertices[0].setPosition(_x + topRight.x, _y + topRight.y);

		//Top left
		_vertices[1].setPosition(_x + topLeft.x, _y + topLeft.y);

		//Bottom left
		_vertices[2].setPosition(_x + bottomLeft.x, _y + bottomLeft.y);

		//Triangle 2
		//Bottom left = vertices[2]

		//Bottom right
		_vertices[3].setPosition(_x + bottomRight.x, _y + bottomRight.y);

		//Top right = vertices[0]
	}

	void Sprite::pointAt(glm::vec2 pos) {
		if(pos.x != _x && pos.y != _y) {
			//Set the pos vector to be centered around the sprite
			pos = pos - glm::vec2(_x, _y) - _center;
			if(pos.x != 0 || pos.y != 0) {
				//Rotate by the angle between the vector (1, 0) and pos 
				//The dot product of (1, 0) with pos simplifies to pos.x / length(pos)
				rotate(acos(pos.x / glm::length(pos)) * (pos.y < 0.0f ? -1.0f : 1.0f));
			}
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