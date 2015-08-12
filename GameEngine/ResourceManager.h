#pragma once
#include <string>
#include <map>
#include "GLTexture.h"
#include "IOManager.h"

namespace GameEngine {
	class ResourceManager {
	public:
		ResourceManager(IOManager* IOManager);
		~ResourceManager();

		GLTexture getTexture(std::string path);

	private:
		std::map<std::string, GLTexture> _textureMap;
		IOManager* _IOManager;
	};
}
