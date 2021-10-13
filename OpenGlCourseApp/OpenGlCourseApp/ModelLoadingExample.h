#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"
class ModelLoadingExample
{
public:
	int run();
private:
	const string vertexShaderSourceCode = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos;"
		"layout(location = 1) in vec3 aNormal;"
		"layout(location = 2) in vec2 aTexCoords;"
		"out vec2 TexCoords;"
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"void main()"
		"{"
			"TexCoords = aTexCoords;"
			"gl_Position = projection * view * model * vec4(aPos, 1.0);"
		"}";
	const string fragmentShaderSourceCode = "#version 330 core\n"
		"out vec4 FragColor;"
		"in vec2 TexCoords;"
		"uniform sampler2D texture_diffuse1;"
		"void main()"
		"{"
		"	FragColor = texture(texture_diffuse1, TexCoords);"
		"}";
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);
};
