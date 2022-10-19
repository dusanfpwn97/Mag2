#include "GLSLProgram.h"
#include "errors.h"
#include <fstream>
#include <vector>
#include <iostream>
namespace efe
{
	GLSLProgram::GLSLProgram() :
		_numAttributes(0),
		_programID(0),
		_vertexShaderID(0),
		_fragmentShaderID(0)
	{

	}

	GLSLProgram::~GLSLProgram()
	{

	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath)
	{
		_programID = glCreateProgram();


		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0)
		{
			fatalError("Vertex Shader failed to be created!");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0)
		{
			fatalError("Fragment Shader failed to be created!");
		}


		compileShader(vertexShaderFilepath, _vertexShaderID);
		compileShader(fragmentShaderFilepath, _fragmentShaderID);


	}

	void GLSLProgram::linkShaders()
	{
		// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.



		// Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		// Link our program
		glLinkProgram(_programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLuint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLsizei maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_programID);
			// Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			std::printf("%s\n", &errorLog[0]);

			fatalError("Shaders failed to link!");

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

	}

	void GLSLProgram::addAttribute(const std::string& attributeName)
	{

		//older way to do it. see layout
		glBindAttribLocation(_programID, _numAttributes, attributeName.c_str());
		_numAttributes++;
	}

	void GLSLProgram::use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unUse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{

		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform" + uniformName + "not found in shader!");
		}


		return location;
	}

	void GLSLProgram::compileShader(const std::string& filepath, GLint id)
	{
		std::ifstream vertexFile(filepath);
		if (vertexFile.fail())
		{
			perror(filepath.c_str());
			fatalError("Failed to open" + filepath);

		}

		std::string fileContents = "";
		std::string line = "";

		while (std::getline(vertexFile, line))
		{
			fileContents += line += "\n";
		}
		vertexFile.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);
		glCompileShader(id);

		GLint isCompiled = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(id); // Don't leak the shader.

			std::printf("%s\n", &errorLog[0]);

			fatalError("Shader " + filepath + "failed to compile");

			return;
		}
	}


}