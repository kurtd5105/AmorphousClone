#include "ResourceManager.h"
#include "IOManager.h"
#include <iostream>
#include <functional>

namespace GameEngine {
	void test(std::string tests) {

	}
	ResourceManager::ResourceManager(IOManager* IOManager) : _IOManager(IOManager) {
	}


	ResourceManager::~ResourceManager() {
	}

	Animation ResourceManager::getAnimation(std::string path) {
		//Check for/load animation here
		return _IOManager->loadAnimation(path);
	}

	//get texture tile
	GLTexture ResourceManager::getTexture(std::string path) {
		auto result = _textureMap.find(path);

		//If it wasn't found fully loaded then load it
		if(result == _textureMap.end()) {
			auto resultRaw = _rawTextureMap.find(path);
			//If it was partially loaded then complete the loading
			if(resultRaw != _rawTextureMap.end()) {
				GLTexture texture = _IOManager->loadRawTex(resultRaw->second);

				_textureMap.insert(make_pair(path, texture));
				std::cout << "New raw texture loaded: " << path << ". ID: " << texture.id << std::endl;
				return texture;
			}
			//The texture wasn't partially loaded so it must be loaded now
			GLTexture newTexture = _IOManager->loadPNG(path);
			_textureMap.insert(make_pair(path, newTexture));
			std::cout << "New texture loaded: " << path << std::endl;
			return newTexture;
		}
		std::cout << "Texture already loaded." << std::endl;
		return result->second;
	}

	void ResourceManager::getTextures(std::vector<std::string> paths, ThreadState* taskState) {
		*taskState = ThreadState::ON;
		for(auto& path : paths) {
			std::cout << ">> Async loading a texture: " << path << std::endl;
			auto result = _textureMap.find(path);
			auto resultRaw = _rawTextureMap.find(path);
			//If it wasn't found then load it
			if(result == _textureMap.end() && resultRaw == _rawTextureMap.end()) {
				GLRawTexture newTexture = _IOManager->loadPNGRaw(path);
				_rawTextureMap.insert(make_pair(path, newTexture));
				std::cout << "> New texture loaded: " << path << std::endl;
			} else {
				std::cout << "> Texture already loaded." << std::endl;
			}
		}
		*taskState = ThreadState::FINISHED;
	}

	void ResourceManager::syncLoadAnimation(std::string path) {
		getAnimation(path);
	}

	void ResourceManager::syncLoadTexture(std::string path) {
		getTexture(path);
	}

	void ResourceManager::asyncLoadAnimation(std::vector<std::string> paths, std::thread& currentThread, ThreadState* taskComplete) {
		//
	}

	void ResourceManager::asyncLoadTexture(std::vector<std::string> paths, std::thread& currentThread, ThreadState* taskState) {
		std::cout << ">> Async texture load called, thread started." << std::endl;
		currentThread = std::thread(&GameEngine::ResourceManager::getTextures, this, paths, taskState);
		//Better performance when thread is detached
		currentThread.detach();
	}
}