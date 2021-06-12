#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

using namespace std;
class HelloTriangle_3 {
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char*fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	const char*fragmentShaderSourceYellow = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\0";

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	static void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
public:
	int run()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
		glViewport(0, 0, 800, 600);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		float vertices_triangle1[] = {
			0.5f,0.5f,0.0f ,
			1.0f,-0.5f,0.0f,
			0,-0.5f,0.0f
		};

		float vertices_triangle2[] = {
			-0.5f,0.5f,0.0f,
			-1.0f,-0.5f,0.0f,
			0,-0.5f,0.0f
		};
		//unsigned int indices[] = { 0 , 1 ,3,3,2,1 };
		unsigned int triangle1VAO;
		glGenVertexArrays(1, &triangle1VAO);
		glBindVertexArray(triangle1VAO);
		unsigned int triangle1VBO;
		glGenBuffers(1, &triangle1VBO);
		glBindBuffer(GL_ARRAY_BUFFER, triangle1VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle1), vertices_triangle1, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		unsigned int triangle2VAO;
		glGenVertexArrays(1, &triangle2VAO);
		glBindVertexArray(triangle2VAO);
		unsigned int triangle2VBO;
		glGenBuffers(1, &triangle2VBO);
		glBindBuffer(GL_ARRAY_BUFFER, triangle2VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle2), vertices_triangle2, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		// shader creation
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		}
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		}
		// program creation
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADERPROGRAM::LINKING_FAILED\n" <<
				infoLog << std::endl;
		}
		
		glDeleteShader(fragmentShader);

		unsigned int yellowShaderProgram;
		yellowShaderProgram = glCreateProgram();
		unsigned int yellowFragmentShader;
		yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(yellowFragmentShader, 1, &fragmentShaderSourceYellow, NULL);
		glCompileShader(yellowFragmentShader);
		if (!success)
		{
			glGetShaderInfoLog(yellowFragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		}
		glAttachShader(yellowShaderProgram, vertexShader);
		glAttachShader(yellowShaderProgram, yellowFragmentShader);
		glLinkProgram(yellowShaderProgram);
		glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(yellowShaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADERPROGRAM::LINKING_FAILED\n" <<
				infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(yellowFragmentShader);


		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			// rendering commands here
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(shaderProgram);
			glBindVertexArray(triangle1VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			glUseProgram(yellowShaderProgram);
			glBindVertexArray(triangle2VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
		return 0;
	}
};
