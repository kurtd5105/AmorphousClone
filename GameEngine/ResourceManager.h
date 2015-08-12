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

		//Allows for dynamic loading of textures
		GLTexture getTexture(std::string path);

		//Synchronously loads a file
		void syncLoadTexture(std::string path);

		//Asynchronously loads a file
		bool asyncLoadTexture(std::string path);

	private:
		std::map<std::string, GLTexture> _textureMap;
		IOManager* _IOManager;
	};
}
