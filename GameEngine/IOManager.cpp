#include "IOManager.h"
#include "picoPNG.h"
#include "Errors.h"
#include <fstream>

namespace GameEngine {
	IOManager::IOManager() {
	}


	IOManager::~IOManager() {
	}

	Animation IOManager::loadAnimation(std::string path) {
		//Parse animation file here
		return Animation();
	}

	GLTexture IOManager::loadPNG(std::string path) {
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

	GLRawTexture IOManager::loadPNGRaw(std::string path) {
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

		buffer.resize(fileSize);
		file.read((char *)&(buffer[0]), fileSize);
		file.close();
		return true;
	}
}