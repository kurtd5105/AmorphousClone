#pragma once
#include <string>
#include <GL/glew.h>
#include "IOManager.h"

namespace GameEngine {
	class ShadingProgram {
	public:
		ShadingProgram();
		~ShadingProgram();

		void ShadingProgram::init(const std::string &vertexPath, const std::string &fragmentPath, IOManager* manager);
		void compileShaders(const std::string &vertexPath, const std::string &fragmentPath);
		void linkShaders();
		void addAttribute(const std::string attributeName);
		void use();
		void unuse();

		GLint getUniformLocation(const std::string uniformName);

	private:
		IOManager* _IOManager;

		GLuint _programID;
		GLuint _vertexID;
		GLuint _fragmentID;
		int _numAttributes;

		GLint compileShader(const std::string shaderPath, GLuint *shaderID);
	};
}
