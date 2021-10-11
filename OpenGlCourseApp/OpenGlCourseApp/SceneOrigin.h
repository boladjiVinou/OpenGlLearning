#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class SceneOrigin
{
private:
	unsigned int _vao, _vbo;
	Shader *_vertexShader, *_fragmentShader;
	const string vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 customFragColor;"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"	gl_Position =  projection * view * model *vec4(aPos, 1.0);\n"
		"	customFragColor = aColor;"
		"}\0";
	const string fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 customFragColor;"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(customFragColor, 1.0f);\n"
		"}\0";
	const string MODEL_MATRIX_NAME = "model";
	const string VIEW_MATRIX_NAME = "view";
	const string PROJECTION_MATRIX_NAME = "projection";
public:
	SceneOrigin();
	~SceneOrigin();
	void displayOrigin(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);
};