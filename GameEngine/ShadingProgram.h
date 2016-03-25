#pragma once
#include <string>
#include <GL/glew.h>
#include "IOManager.h"

namespace GameEngine {
	class ShadingProgram {
	public:
		ShadingProgram();
		~ShadingProgram();

		void ShadingProgram::init(const std::string &vertexPath, const std::string &fragmentPath, std::vector<std::string> attributes, IOManager* manager);
		void compileShaders(const std::string &vertexPath, const std::string &fragmentPath);
		void linkShaders() const;
		void addAttribute(const std::string attributeName);
		void use() const;
		void unuse() const;

		GLint getUniformLocation(const std::string uniformName) const;

	private:
		IOManager* _IOManager;

		GLuint _programID;
		GLuint _vertexID;
		GLuint _fragmentID;
		int _numAttributes;

		GLint compileShader(const std::string shaderPath, GLuint *shaderID) const;
	};
}
