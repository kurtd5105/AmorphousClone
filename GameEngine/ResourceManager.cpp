#include "ResourceManager.h"
#include "IOManager.h"
#include <iostream>

namespace GameEngine {
	void test(std::string tests) {

	}
	ResourceManager::ResourceManager(IOManager* IOManager) : _IOManager(IOManager) {}

	ResourceManager::~ResourceManager() {}

	Animation ResourceManager::getAnimation(std::string path) {
		auto result = _animationMap.find(path);

		//If it wasn't found fully loaded then load it
		if(result == _animationMap.end()) {
			Animation newAnimation = _IOManager->loadAnimation(path);
			_animationMap.insert(make_pair(path, newAnimation));
			std::cout << "New animation loaded: " << path << std::endl;
			return newAnimation;
		}
		std::cout << "Animation already loaded: " << path << std::endl;
		return result->second;
	}

	Font ResourceManager::getFont(std::string path, int point) {
		char temp[3];
		_itoa_s(point, temp, 10);
		std::string pathPoint = path + ":" + temp;
		//std::cout << "Font: " << path << " ID string: " << pathPoint << std::endl;
		auto result = _fontMap.find(pathPoint);

		//If it wasn't found fully loaded then load it
		if(result == _fontMap.end()) {
			Font newFont;
			newFont.init(path, point);
			_fontMap.insert(make_pair(pathPoint, newFont));
			std::cout << "New font loaded: " << path << std::endl;
			return newFont;
		}
		std::cout << "Font already loaded: " << path << std::endl;
		return result->second;
	}

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
		//std::cout << "Texture already loaded." << std::endl;
		return result->second;
	}

	void ResourceManager::syncLoadAnimation(std::string path) {
		getAnimation(path);
	}

	void ResourceManager::syncLoadFont(std::string path, int point) {
		getFont(path, point);
	}

	void ResourceManager::syncLoadTexture(std::string path) {
		getTexture(path);
	}

	void ResourceManager::asyncAssetLoad(std::vector<std::string> textures, std::vector<std::string> animations, std::thread& currentThread, ThreadState* taskState) {
		std::cout << ">> Async asset load called, thread started." << std::endl;
		currentThread = std::thread(&GameEngine::ResourceManager::asyncLoad, this, textures, animations, taskState);
		//Better performance when thread is detached
		currentThread.detach();
	}

	void ResourceManager::asyncLoad(std::vector<std::string> textures, std::vector<std::string> animations, ThreadState* taskState) {
		*taskState = ThreadState::ON;
		asyncLoadTextures(textures);
		asyncLoadAnimations(animations);
		*taskState = ThreadState::FINISHED;
	}

	void ResourceManager::asyncLoadAnimations(std::vector<std::string> paths) {
		for(auto& path : paths) {
			std::cout << ">> Async loading an animation: " << path << std::endl;
			getAnimation(path);
		}
	}

	void ResourceManager::asyncLoadTextures(std::vector<std::string> paths) {
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
	}

	
}