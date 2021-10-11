#include "Shader.h"
Shader::Shader(string shaderContent, GLenum type)
{
	int success;
	char infoLog[512];
	_shaderId = glCreateShader(type);
	const char* shaderCodePointer = shaderContent.c_str();
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
Shader Shader::FromFile(string shaderPath, GLenum type)
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
	return Shader(shaderCode, type);
}
// attach shader to program and destroy it
void Shader::AttachShaderTo(unsigned int programId)
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
	else
	{
		glDeleteShader(_shaderId);
	}
}
// utility uniform functions
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(_programId, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(_programId, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(_programId, name.c_str()), value);
}
void Shader::setMat4(const std::string &name, const glm::mat4 &value)const
{
	glUniformMatrix4fv(glGetUniformLocation(_programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setMat3(const std::string &name, const glm::mat3 &value)const
{
	glUniformMatrix3fv(glGetUniformLocation(_programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value)const
{
	glUniform3fv(glGetUniformLocation(_programId, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::useProgram()
{
	glUseProgram(_programId);
}