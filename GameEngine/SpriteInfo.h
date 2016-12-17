#pragma once
#include "SpriteManager.h"
#include <string>
#include <vector>

namespace GameEngine {
	class SpriteInfo {
	public:
		SpriteInfo(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path, SpriteManager* manager) {
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->depth = depth;
			this->UVmM = UVmM;
			this->path = path;
			this->manager = manager;
		}

		virtual ~SpriteInfo() noexcept = default;

		float x;
		float y;
		float width;
		float height;
		float depth;
		std::vector<float> UVmM;
		std::string path;
		SpriteManager* manager;
	};
}
