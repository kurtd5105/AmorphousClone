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

		//Allows for dynamic loading of texture data while gl context isn't available (each thread requires gl context otherwise)
		GLTexture getTexture(std::string path);
		void getTextures(std::vector<std::string> paths, ThreadState* taskState);


		//Synchronously loads a file
		void syncLoadAnimation(std::string path);
		void syncLoadTexture(std::string path);

		//Asynchronously loads a file
		void asyncLoadAnimation(std::vector<std::string> paths, std::thread& currentThread, ThreadState* taskComplete);
		void asyncLoadTexture(std::vector<std::string> paths, std::thread& currentThread, ThreadState* taskComplete);

		//Debug getters for amount of textures
		int getRawCount() { return _rawTextureMap.size(); }
		int getTexCount() { return _textureMap.size(); }

	private:
		std::map<std::string, Animation> _animationMap;
		std::map<std::string, GLTexture> _textureMap;
		std::map<std::string, GLRawTexture> _rawTextureMap;
		IOManager* _IOManager;
	};
}
