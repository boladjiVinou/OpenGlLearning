#pragma once
#include "Shader.cpp"
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class SceneOrigin 
{
private:
	unsigned int _vao,_vbo;
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
	SceneOrigin() 
	{
		float vertices_color[] = 
		{
			0.0f,0.0f,0.0f,			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,			1.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,			0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,			0.0f,0.0f,1.0f,
		};
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_color), vertices_color, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		unsigned int shaderProgram = glCreateProgram();
		_vertexShader =new Shader(vertexShaderSource, GL_VERTEX_SHADER);
		_fragmentShader =new Shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
		_vertexShader->AttachShaderTo(shaderProgram);
		_fragmentShader->AttachShaderTo(shaderProgram);
	}
	~SceneOrigin() 
	{
		delete _vertexShader;
		_vertexShader = nullptr;
		delete _fragmentShader;
		_fragmentShader = nullptr;
	}
	void displayOrigin(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix)
	{
		glBindVertexArray(_vao);
		_vertexShader->useProgram();
		_vertexShader->setMat4(MODEL_MATRIX_NAME, glm::mat4(1.0f));
		_vertexShader->setMat4(VIEW_MATRIX_NAME, viewMatrix);
		_vertexShader->setMat4(PROJECTION_MATRIX_NAME, projectionMatrix);
		glDrawArrays(GL_LINES, 0, 6);
	}
};