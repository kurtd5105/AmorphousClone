#include "ShadingProgram.h"
#include "IOManager.h"
#include "Errors.h"
#include <vector>

namespace GameEngine {
	ShadingProgram::ShadingProgram() : _IOManager(nullptr), _programID(0), _vertexID(0), _fragmentID(0), _numAttributes(0) {
	}


	ShadingProgram::~ShadingProgram() {
	}

	void ShadingProgram::init(const std::string &vertexPath, const std::string &fragmentPath, std::vector<std::string> attributes, IOManager* manager) {
		_IOManager = manager;
		compileShaders(vertexPath, fragmentPath);
		for(auto& attribute : attributes) {
			addAttribute(attribute);
		}
		linkShaders();
	}

	GLint ShadingProgram::compileShader(const std::string shaderPath, GLuint *shaderID) const {
		std::vector<unsigned char> fileBuffer;
		if(!_IOManager->readFileToBuffer(shaderPath, fileBuffer)) {
			fatalIOError(shaderPath);
		}
		auto contents = std::string(fileBuffer.begin(), fileBuffer.end());

		auto contentsPtr = contents.c_str();
		glShaderSource(*shaderID, 1, &contentsPtr, nullptr);
		glCompileShader(*shaderID);

		GLint result = 0;
		glGetShaderiv(*shaderID, GL_COMPILE_STATUS, &result);
		if(result == GL_FALSE) {
			GLint len = 0;
			glGetShaderiv(*shaderID, GL_INFO_LOG_LENGTH, &len);
			std::vector<GLchar> errorLog(len);
			glGetShaderInfoLog(*shaderID, len, &len, &errorLog[0]);

			glDeleteShader(*shaderID);

			std::printf("%s\n", &errorLog[0]);
		}

		return result;
	}

	void ShadingProgram::compileShaders(const std::string &vertexPath, const std::string &fragmentPath) {
		//Add error checking for this!
		_programID = glCreateProgram();

		//Create the vertex shader
		_vertexID = glCreateShader(GL_VERTEX_SHADER);
		if(_vertexID == 0) {
			fatalGenericError("Creation of vertex shader failed.");
		}

		//Create the fragment shader
		_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		if(_fragmentID == 0) {
			fatalGenericError("Creation of fragment shader failed.");
		}

		//Compile each shader
		auto vertexResult = compileShader(vertexPath, &_vertexID);
		if(vertexResult == GL_FALSE) {
			fatalGenericError("Vertex shader " + vertexPath + " failed to compile.");
		}

		auto fragmentResult = compileShader(fragmentPath, &_fragmentID);
		if(fragmentResult == GL_FALSE) {
			fatalGenericError("Fragment shader " + fragmentPath + " failed to compile.");
		}


	}

	void ShadingProgram::addAttribute(const std::string attributeName) {
		//Add an attribute to the program
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	GLint ShadingProgram::getUniformLocation(const std::string uniformName) const {
		//Get and return the location of a uniform
		auto location = glGetUniformLocation(_programID, uniformName.c_str());
		if(location == GL_INVALID_INDEX) {
			fatalGenericError("Uniform " + uniformName + " not found.");
		}
		return location;
	}

	void ShadingProgram::linkShaders() const {
		//Attach both shaders to the program
		glAttachShader(_programID, _vertexID);
		glAttachShader(_programID, _fragmentID);
		//Link the program
		glLinkProgram(_programID);

		//Get the result of the linking
		GLint result = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, &result);

		//If the linking failed, retrieve the error and clean up the useless shaders and program
		if(result == GL_FALSE) {
			GLint len = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &len);
			std::vector<GLchar> errorLog(len);
			glGetProgramInfoLog(_programID, len, &len, &errorLog[0]);

			glDeleteProgram(_programID);
			glDeleteShader(_vertexID);
			glDeleteShader(_fragmentID);

			std::printf("%s\n", &errorLog[0]);
			fatalGenericError("Program failed to link.");
		}

		//After successful linking, detach and delete the unneeded shaders
		glDetachShader(_programID, _vertexID);
		glDetachShader(_programID, _fragmentID);
		glDeleteShader(_vertexID);
		glDeleteShader(_fragmentID);
	}

	void ShadingProgram::use() const {
		//Start using the shading program and enable its attributes
		glUseProgram(_programID);
		for(int i = 0; i < _numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void ShadingProgram::unuse() const {
		//Stop using the shading program and disable its attributes
		glUseProgram(0);
		for(auto i = 0; i < _numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}
}