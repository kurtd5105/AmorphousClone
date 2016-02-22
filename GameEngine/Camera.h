#pragma once
#include <glm/glm.hpp>

namespace GameEngine {
	class Camera {
	public:
		Camera();
		~Camera();

		const float CAMERA_SPEED = 0.05f;
		const float SCALE_SPEED = 0.0001f;

		void init(int width, int height);
		void update();
		glm::vec2 toWorldCoords(glm::vec2 pos) const;

		//Setters
		void setPosition(const glm::vec2& newPos) { _position = newPos; _needsUpdate = true; }
		void setScale(const float& newScale) { _scale = newScale; _needsUpdate = true; }

		//Getters
		glm::vec2 getPosition() const { return _position; }
		glm::mat4 getMatrix() const { return _cameraMatrix; }
		float* getMatrixRef() { return &_cameraMatrix[0][0]; }
		float getScale() const { return _scale; }

	private:
		bool _needsUpdate;
		float _scale;
		int _width, _height;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};
}
