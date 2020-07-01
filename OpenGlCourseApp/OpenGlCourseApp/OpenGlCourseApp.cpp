// OpenGlCourseApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<string>
using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader, uniformXMove;

// vertex shader
static const char* vShader = "														\n\
#version 330																		\n\
layout (location = 0) in vec3 pos;													\n\
uniform float xMove;																	\n\
void main()																			\n\
{																					\n\
	gl_Position = vec4(0.4f *pos.x + xMove, 0.4f *pos.y, pos.z,1.0);									\n\
}																					\n\
";
// fragment shader
static const char* fShader= "														\n\
#version 330																		\n\
out vec4 color;																		\n\
void main()																			\n\
{																					\n\
	color = vec4(1.0, 0.0, 0.0,1.0);												\n\
}																					\n\
";
bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

void AddShader(GLuint theProgram, const char * shaderCode, GLenum shaderType) 
{
	GLuint theShader = glCreateShader(shaderType);
	
	const GLchar * theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
		cout << "Error compiling "<<shaderType<< " shader : " << eLog << endl;
	}
	glAttachShader(theProgram, theShader);
}
void CompileShader()
{
	shader = glCreateProgram();

	if (!shader)
	{
		cout << "Error creating shader program ! " << endl;
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result) 
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error linking program : " << eLog << endl;
	}

	glValidateProgram(shader);

	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error validating program : " << eLog << endl;
	}

	uniformXMove = glGetUniformLocation(shader, "xMove");
}
void CreateTriangle()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f,-1.0, 0.0f,
		0.0,1.0f,0.0f
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
int main()
{
	//Initialize  glfw
	if (!glfwInit())
	{
		cout << "GLFW Initialization failed" << endl;
		glfwTerminate();
		return 1;
	}
	// setup glfw window properties
	// opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// core profile - no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ALLOW forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow * mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow) 
	{
		cout << "GLFW window creation failed !" << endl;
		glfwTerminate();
		return 1;
	}
	// Get Buffer size Information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// set context for glew to use
	glfwMakeContextCurrent(mainWindow);

	//allow modern extension features
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK)
	{
		cout << "GLEW initialisation failed !" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}


	// ssetup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);


	CreateTriangle();
	CompileShader();


	// loop until window closed

	while (!glfwWindowShouldClose(mainWindow)) 
	{
		// Get + Handle input events
		glfwPollEvents();

		if (direction) {
			triOffset += triIncrement;
		}
		else {
			triOffset -= triIncrement;
		}
		if (abs(triOffset) >= triMaxOffset) 
		{
			direction = !direction;
		}
		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glUniform1f(uniformXMove, triOffset);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
