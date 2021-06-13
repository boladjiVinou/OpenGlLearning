#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
public:
	// the program ID
	unsigned int _programId;
	unsigned int _shaderId;
	// constructor reads and builds the shader
	Shader(const char* shaderPath, GLenum type)
	{
		std::string shaderCode;
		std::ifstream shaderFile;
		// ensure ifstream objects can throw exceptions:
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			shaderFile.open(shaderPath);
			std::stringstream shaderStream;
			// read file’s buffer contents into streams
			shaderStream << shaderStream.rdbuf();
			// close file handlers
			shaderFile.close();
			// convert stream into string
			shaderCode = shaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* shaderCodePointer = shaderCode.c_str();
		// 2. compile shaders
		int success;
		char infoLog[512];
		_shaderId = glCreateShader(type);
		glShaderSource(_shaderId, 1, &shaderCodePointer, NULL);
		glCompileShader(_shaderId);
		// print compile errors if any
		glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_shaderId, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		};
	}
	void AttachShaderTo(unsigned int programId) 
	{
		glAttachShader(programId, _shaderId);
		glLinkProgram(programId);
		_programId = programId;
		int success;
		char infoLog[512];
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
				infoLog << std::endl;
		}
	}
	// utility uniform functions
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(_programId, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(_programId, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(_programId, name.c_str()), value);
	}
};
#endif