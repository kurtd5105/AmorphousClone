#pragma once
#include <string>
#include <vector>

#include "Animation.h"
#include "GLTexture.h"

namespace GameEngine {
	class IOManager {
	public:
		IOManager();
		~IOManager();

		Animation loadAnimation(std::string path);
		GLTexture loadPNG(std::string path);
		GLRawTexture loadPNGRaw(std::string path);
		GLTexture loadRawTex(GLRawTexture raw);
		bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}
