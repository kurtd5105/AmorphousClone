#include "ResourceManager.h"
#include "IOManager.h"
#include <iostream>

namespace GameEngine {
	void test(std::string tests) {

	}
	ResourceManager::ResourceManager(IOManager* IOManager) : _IOManager(IOManager) {
	}


	ResourceManager::~ResourceManager() {
	}

	GLTexture ResourceManager::getTexture(std::string path) {
		auto result = _textureMap.find(path);

		//If it wasn't found then load it
		if(result == _textureMap.end()) {
			auto resultRaw = _rawTextureMap.find(path);
			if(resultRaw != _rawTextureMap.end()) {
				GLTexture texture = {};
				texture.width = resultRaw->second.width;
				texture.height = resultRaw->second.height;

				glGenTextures(1, &texture.id);
				glBindTexture(GL_TEXTURE_2D, texture.id);
				//&(out[0])
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(resultRaw->second.data[0]));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				glGenerateMipmap(GL_TEXTURE_2D);

				//Unbind the texture afterwards
				glBindTexture(GL_TEXTURE_2D, 0);

				_textureMap.insert(make_pair(path, texture));
				std::cout << "New raw texture loaded: " << path << ". ID: " << texture.id << std::endl;
				return texture;
			}

			GLTexture newTexture = _IOManager->loadPNG(path);
			_textureMap.insert(make_pair(path, newTexture));
			std::cout << "New texture loaded." << std::endl;
			return newTexture;
		}
		std::cout << "Texture already loaded." << std::endl;
		return result->second;
	}

	void ResourceManager::getTextures(std::vector<std::string> paths) {
		for(auto& path : paths) {
			auto result = _textureMap.find(path);

			//If it wasn't found then load it
			if(result == _textureMap.end()) {
				GLRawTexture newTexture = _IOManager->loadPNGRaw(path);
				_rawTextureMap.insert(make_pair(path, newTexture));
				std::cout << "New texture loaded." << std::endl;
			}
			std::cout << "Texture already loaded." << std::endl;
		}
	}

	void getTexturesB(std::vector<std::string> paths, std::map<std::string, GLTexture>* _textureMap, std::map<std::string, GLRawTexture>* _rawTextureMap,
					  IOManager* _IOManager, ThreadState* taskState) {
		*taskState = ThreadState::ON;
		for(auto& path : paths) {
			std::cout << "Async loading a texture." << std::endl;
			auto result = _textureMap->find(path);
			auto resultRaw = _rawTextureMap->find(path);
			//If it wasn't found then load it
			if(result == _textureMap->end() && resultRaw == _rawTextureMap->end()) {
				GLRawTexture newTexture = _IOManager->loadPNGRaw(path);
				_rawTextureMap->insert(make_pair(path, newTexture));
				std::cout << "New texture loaded." << std::endl;
			} else {
				std::cout << "Texture already loaded." << std::endl;
			}
		}
		*taskState = ThreadState::FINISHED;
	}

	void ResourceManager::syncLoadTexture(std::string path) {
		getTexture(path);
	}

	void ResourceManager::asyncLoadTexture(std::vector<std::string> paths, std::thread& currentThread, ThreadState* taskState) {
		std::cout << "Async texture load called." << std::endl;
		currentThread = std::thread(getTexturesB, paths, &_textureMap, &_rawTextureMap, _IOManager, taskState);
		currentThread.detach();
	}
}