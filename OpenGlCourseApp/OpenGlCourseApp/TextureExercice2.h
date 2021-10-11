#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"

#include "Shader.h"

class TextureExercice2 {
	const string vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 2) in vec2 aTexCoord;"
		"out vec4 ourColor;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		" ourColor =gl_Position;\n"
		" TexCoord = aTexCoord;\n"
		"}\0";

	const string fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 ourColor;"
		"in vec2 TexCoord;\n"
		"uniform sampler2D texture1;"
		"uniform sampler2D texture2;"
		"void main()\n"
		"{\n"
		"   vec2 faceTextCoord = TexCoord;"
		"	FragColor = mix( texture(texture1, TexCoord),"
		"					 texture(texture2, faceTextCoord),"
		"							 0.2);\n"
		"}\0";


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);
public:
	int run();

};
