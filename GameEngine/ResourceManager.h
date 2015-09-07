#pragma once
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "GLTexture.h"
#include "IOManager.h"
#include "ThreadState.h"

namespace GameEngine {
	class ResourceManager {
	public:
		ResourceManager(IOManager* IOManager);
		~ResourceManager();

		//Allows for dynamic loading of textures
		GLTexture getTexture(std::string path);
		void getTextures(std::vector<std::string> paths, ThreadState* taskState);


		//Synchronously loads a file
		void syncLoadTexture(std::string path);

		//Asynchronously loads a file
		void asyncLoadTexture(std::vector<std::string> paths, std::thread& currentThread, ThreadState* taskComplete);

		//Debug getters for amount of textures
		int getRawCount() { return _rawTextureMap.size(); }
		int getTexCount() { return _textureMap.size(); }

	private:
		std::map<std::string, GLTexture> _textureMap;
		std::map<std::string, GLRawTexture> _rawTextureMap;
		IOManager* _IOManager;
	};
}
