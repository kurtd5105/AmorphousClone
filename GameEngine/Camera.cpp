#include "Camera.h"

namespace GameEngine {
	Camera::Camera() : _position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_needsUpdate(true),
		_width(0),
		_height(0) {
	}


	Camera::~Camera() {
	}

	void Camera::init(int width, int height) {
		_width = width;
		_height = height;
		_orthoMatrix = glm::ortho(0.0f, (float)_width, 0.0f, (float)_height);
	}

	void Camera::update() {
		if(_needsUpdate) {
			glm::vec3 translate(-_position.x, -_position.y, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			glm::vec3 scale(_scale, _scale, 1.0f);
			_cameraMatrix = glm::scale(_cameraMatrix, scale);

			_needsUpdate = false;
		}
	}

	glm::vec2 Camera::toWorldCoords(glm::vec2 pos) {
		//Invert Y direction
		pos.y = _height - pos.y;
		return pos;
		//Center, scale then move position back
		//return ((pos - glm::vec2(_width / 2, _height / 2)) / _scale) + _position;
	}
}