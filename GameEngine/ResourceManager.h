#pragma once
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "Animation.h"
#include "GLTexture.h"
#include "IOManager.h"
#include "ThreadState.h"

namespace GameEngine {
	class ResourceManager {
	public:
		ResourceManager(IOManager* IOManager);
		~ResourceManager();

		Animation getAnimation(std::string path);
		GLTexture getTexture(std::string path);

		//Synchronously loads a file
		void syncLoadAnimation(std::string path);
		void syncLoadTexture(std::string path);

		void asyncAssetLoad(std::vector<std::string> textures, std::vector<std::string> animations, std::thread& currentThread, ThreadState* taskState);

		//Debug getters for amount of textures
		int getRawCount() { return _rawTextureMap.size(); }
		int getTexCount() { return _textureMap.size(); }

	private:
		std::map<std::string, Animation> _animationMap;
		std::map<std::string, GLTexture> _textureMap;
		std::map<std::string, GLRawTexture> _rawTextureMap;
		IOManager* _IOManager;

		//Handles the async loading of textures and animations
		void asyncLoad(std::vector<std::string> textures, std::vector<std::string> animations, ThreadState* taskState);
		//Asynchronously loads a file list
		void asyncLoadAnimations(std::vector<std::string> paths);
		//Allows for dynamic loading of texture data while gl context isn't available (each thread requires gl context otherwise)
		void asyncLoadTextures(std::vector<std::string> paths);
	};
}
