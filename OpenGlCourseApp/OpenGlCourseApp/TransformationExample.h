#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

//#include "stb_image.h"
class TransformationExample {
	const string vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 2) in vec2 aTexCoord;"
		"uniform mat4 transform;\n"
		"out vec4 ourColor;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		" gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		" ourColor =gl_Position;\n"
		" TexCoord = aTexCoord;\n"
		"}\0";

	const string fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 ourColor;"
		"in vec2 TexCoord;\n"
		//"uniform vec4 ourColor;\n"
		"uniform sampler2D texture1;"
		"uniform sampler2D texture2;"
		"void main()\n"
		"{\n"
		"	FragColor = mix( texture(texture1, TexCoord),"
		"					 texture(texture2, TexCoord),"
		"							 0.2);\n"
		"}\0";


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);
public:
	int run();

};
