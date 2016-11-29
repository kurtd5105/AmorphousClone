#include "IOManager.h"
#include "Errors.h"
#include "Options.h"
#include "picoPNG.h"

#include <regex>
#include <string>

namespace GameEngine {
	IOManager::IOManager() {}

	IOManager::~IOManager() {}

	Animation IOManager::loadAnimation(std::string path) {
		std::vector<unsigned char> in;
		Animation newAnimation;
		
		//Read file and check for load errors
		if(!readFileToBuffer(path, in)) {
			fatalIOError(path);
		}

		//Setup the animation and parse the data
		newAnimation.init(in);
		newAnimation.parseData();
		return newAnimation;
	}

	GLTexture IOManager::loadPNG(std::string path) const {
		GLTexture texture = {};
		std::vector<unsigned char> in;
		std::vector<unsigned char> out;
		unsigned long width, height;

		//Read file and check for load errors
		if(!readFileToBuffer(path, in)) {
			fatalIOError(path);
		}

		//Decode the PNG and check for errors
		int error = decodePNG(out, width, height, &(in[0]), in.size());

		if(error != 0) {
			fatalPicoError(std::to_string(error));
		}

		//Setup the GL textures and parameters
		glGenTextures(1, &texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		glGenerateMipmap(GL_TEXTURE_2D);

		texture.width = width;
		texture.height = height;

		//Unbind the texture afterwards
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}

	GLRawTexture IOManager::loadPNGRaw(std::string path) const {
		std::vector<unsigned char> in;
		std::vector<unsigned char> out;
		unsigned long width, height;

		GLRawTexture texture = {};

		//Read file and check for load errors
		if(!readFileToBuffer(path, in)) {
			fatalIOError(path);
		}

		//Decode the PNG and check for errors
		int error = decodePNG(out, width, height, &(in[0]), in.size());

		if(error != 0) {
			fatalPicoError(std::to_string(error));
		}

		texture.width = width;
		texture.height = height;
		texture.data = out;

		return texture;
	}

	GLTexture IOManager::loadRawTex(GLRawTexture raw) {
		GLTexture texture = {};
		texture.width = raw.width;
		texture.height = raw.height;

		glGenTextures(1, &texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(raw.data[0]));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind the texture afterwards
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
		std::ifstream file(filePath, std::ios::binary);

		//Check if the file couldn't be opened
		if(file.fail()) {
			perror(filePath.c_str());
			return false;
		}
		//Seek to the end to get file size then back to the start to read like normal
		file.seekg(0, std::ios::end);
		auto fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		//Reduce file size by anything that won't be read at the start
		fileSize -= file.tellg();

		buffer.resize(unsigned int(fileSize));
		file.read(reinterpret_cast<char *>(&(buffer[0])), fileSize);
		file.close();
		return true;
	}

	void IOManager::loadOptions(Options* options) const {
		std::ifstream file("options.cfg");

		options->width = 800;
		options->height = 600;
		options->music = 1.0f;
		options->sfx = 1.0f;
		options->mode = WindowMode::WINDOWED;

		if(file.is_open()) {
			//std::cout << "File is open." << std::endl;
			std::string width, height, spawnCount, spawnRate, music, sfx, mode;
			std::regex integer("[[:digit:]]+"); //(unsigned integer since there can't be a '-' in front)
			std::regex decimal("[[:digit:]]+(.[[:digit:]]+)?");
			file >> width;
			file >> height;
			file >> spawnCount;
			file >> spawnRate;
			file >> music;
			file >> sfx;
			file >> mode;

			//Check to see if width and height can be parsed to integers
			if(regex_match(width, integer) && regex_match(height, integer)) {
				//std::cout << "\t> WH match found." << std::endl;
				int w = std::stoi(width);
				int h = std::stoi(height);
				unsigned int i;

				//Check to see if the provided width and height are a valid display resolution
				for(i = 0; i < GameEngine::Screen::validWidths.size(); i++) {
					if(GameEngine::Screen::validWidths[i] == w) {
						if(GameEngine::Screen::validHeights[i] == h) {
							//std::cout << "\t\tWH are valid." << std::endl;
							options->width = w;
							options->height = h;
						}
						break;
					}
				}
			}

			if(regex_match(spawnCount, integer)) {
				unsigned int c = std::stoi(spawnCount);
				options->spawnCount = c;
			}
			if(regex_match(spawnRate, integer)) {
				unsigned int r = std::stoi(spawnRate);
				options->spawnRate = r;
			}

			//Check to see if music volume is a float from 0 to 1
			if(regex_match(music, decimal)) {
				//std::cout << "\t> Music match found." << std::endl;
				auto v = std::stof(music);
				if(v >= 0.0f && v <= 1.0f) {
					//std::cout << "\t\t Music is valid." << std::endl;
					options->music = v;
				}
			}

			//Check to see if sfx volume is a float from 0 to 1
			if(regex_match(sfx, decimal)) {
				//std::cout << "\t> SFX match found." << std::endl;
				auto v = std::stof(sfx);
				if(v >= 0.0f && v <= 1.0f) {
					//std::cout << "\t\t SFX is valid." << std::endl;
					options->sfx = v;
				}
			}

			//Check to see if the window mode is set to any of the window modes
			if(mode == "BORDERLESS") {
				//std::cout << "\t> Borderless." << std::endl;
				options->mode = WindowMode::BORDERLESS;
			} else if(mode == "FULLSCREEN") {
				//std::cout << "\t> Fullscreen." << std::endl;
				options->mode = WindowMode::FULLSCREEN;
			} else if(mode == "WINDOWED") {
				//std::cout << "\t> Windowed." << std::endl;
				options->mode = WindowMode::WINDOWED;
			}
		}
	}

	void IOManager::saveOptions(Options* options) {
		//Open the file for reading and clearing it
		std::ofstream file("options.cfg", std::ios::out | std::ios::trunc);
		file << options->width << std::endl << options->height << std::endl << options->spawnCount << std::endl << options->spawnRate << std::endl
			 << options->music << std::endl << options->sfx << std::endl;

		if(options->mode == WindowMode::BORDERLESS) {
			file << "BORDERLESS" << std::endl;
		} else if(options->mode == WindowMode::FULLSCREEN) {
			file << "FULLSCREEN" << std::endl;
		} else if(options->mode == WindowMode::WINDOWED) {
			file << "WINDOWED" << std::endl;
		}
	}
}