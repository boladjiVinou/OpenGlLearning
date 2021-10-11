#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"

#include "Shader.h"

class TextureExercice3 {
	const string vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 2) in vec2 aTexCoord;"
		"layout (location = 3) in vec2 aFaceTexCoord;"
		"out vec4 ourColor;\n"
		"out vec2 TexCoord;\n"
		"out vec2 faceTexCoord;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		" faceTexCoord = aFaceTexCoord;\n"
		" ourColor =gl_Position;\n"
		" TexCoord = aTexCoord;\n"
		"}\0";

	const string fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 ourColor;"
		"in vec2 TexCoord;\n"
		"in vec2 faceTexCoord; \n"
		"uniform sampler2D texture1;"
		"uniform sampler2D texture2;"
		"void main()\n"
		"{\n"
		"	FragColor = mix( texture(texture1, TexCoord),"
		"					 texture(texture2, faceTexCoord),"
		"							 0.2);\n"
		"}\0";


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);
public:
	int run();

};
