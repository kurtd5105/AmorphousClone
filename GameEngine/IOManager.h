#pragma once
#include <fstream>
#include <vector>

#include "Animation.h"
#include "GLTexture.h"
#include "Options.h"
#include "Window.h"


namespace GameEngine {
	class IOManager {
	public:
		IOManager();
		~IOManager();

		static Animation loadAnimation(std::string path);
		GLTexture loadPNG(std::string path) const;
		GLRawTexture loadPNGRaw(std::string path) const;
		static GLTexture loadRawTex(GLRawTexture raw);
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

		void loadOptions(Options* options) const;
		static void saveOptions(Options* options);

		//const std::vector<int> validWidths = std::vector<int>{800, 1024, 1280, 1360, 1366, 1440, 1600, 1980};
		//const std::vector<int> validHeights = std::vector<int>{600, 768, 720, 768, 768, 900, 900, 1080};
	private:
		const std::string OPTIONS_FILE = "options.cfg";
	};
}
