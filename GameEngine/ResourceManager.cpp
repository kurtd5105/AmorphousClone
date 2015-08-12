#include "ResourceManager.h"
#include "IOManager.h"

namespace GameEngine {
	ResourceManager::ResourceManager(IOManager* IOManager) : _IOManager(IOManager) {
	}


	ResourceManager::~ResourceManager() {
	}

	GLTexture ResourceManager::getTexture(std::string path) {
		auto result = _textureMap.find(path);

		//If it wasn't found then load it
		if(result == _textureMap.end()) {
			GLTexture newTexture = _IOManager->loadPNG(path);
			_textureMap.insert(make_pair(path, newTexture));
			return newTexture;
		}
		return result->second;
	}

	void ResourceManager::syncLoadTexture(std::string path) {
		getTexture(path);
	}

	bool ResourceManager::asyncLoadTexture(std::string path) {
		return false;
	}
}