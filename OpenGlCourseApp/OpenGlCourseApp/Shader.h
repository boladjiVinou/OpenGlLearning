#pragma once
#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
class Shader
{
public:
	
	// the program ID
	unsigned int _programId;
	unsigned int _shaderId;
	// constructor reads and builds the shader

	Shader(string shaderContent, GLenum type);
	static Shader FromFile(string shaderPath, GLenum type);
	// attach shader to program and destroy it
	void AttachShaderTo(unsigned int programId);
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, const glm::mat4 &value)const;
	void setMat3(const std::string &name, const glm::mat3 &value)const;
	void setVec3(const std::string &name, const glm::vec3 &value)const;
	void useProgram();
};