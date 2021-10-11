#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h""

using namespace std;
class ShaderExercice2 {
	string vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec4 ourColor;\n"
		"uniform float offset;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);\n"
		" ourColor = vec4(aColor, 1.0);\n"
		"}\0";
	string fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 ourColor;"
		"void main()\n"
		"{\n"
		"	FragColor =ourColor;\n"
		"}\0";

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);
public:
	int run();

};
