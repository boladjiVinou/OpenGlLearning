#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"

#include "Shader.cpp"
#include "Camera.h"

//#include "stb_image.h"
class ColorsExample {
	const string vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"out vec3 Normal;"
		"out vec3 FragPos;"
		"uniform mat4 model;\n"
		"uniform mat3 NormalModel;"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
		"	FragPos = vec3(model * vec4(aPos, 1.0));"
		"   Normal =NormalModel*aNormal; "
		"}\n";

	const string fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec3 objectColor;\n"
		"uniform vec3 lightColor;\n"
		"uniform vec3 lightPos;\n"
		"uniform vec3 viewPos;"
		"in vec3 Normal;"
		"in vec3 FragPos;"
		"void main()\n"
		"{\n"
			"float ambientStrength = 0.1;\n"
			"vec3 ambient = ambientStrength * lightColor; \n"
			"vec3 norm = normalize(Normal);"
			"vec3 lightDir = normalize(lightPos - FragPos); "
			"float diff = max(dot(norm, lightDir), 0.0);"
			"vec3 diffuse = diff * lightColor; "
			"vec3 viewDir = normalize(viewPos - FragPos);"
			"vec3 reflectDir = reflect(-lightDir, norm);"
			"float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
			"float specularStrength = 0.5;"
			"vec3 specular = specularStrength * spec * lightColor;"
			"vec3 result = (diffuse + ambient + specular)* objectColor; \n"
			"FragColor = vec4(result, 1.0); \n"
		"}\n";

	const string lightFragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0);\n"
		"}\n";


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

		float vertices[] = {
			// positions // normals // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};
		unsigned int indices[] = { 0, 1, 3, 3, 2, 1 };
		unsigned int VAO, lightVAO;
		glGenVertexArrays(1, &VAO);
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(VAO);
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(VAO);


		Shader vertexShader = Shader(vertexShaderSource, GL_VERTEX_SHADER);
		unsigned int shaderProgram = glCreateProgram();
		vertexShader.AttachShaderTo(shaderProgram);
		Shader fragmentShader = Shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
		fragmentShader.AttachShaderTo(shaderProgram);
		fragmentShader.useProgram();
		fragmentShader.setVec3("objectColor",glm::vec3(1.0f, 0.5f, 0.31f));//objectColor
		fragmentShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));


		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		Camera cam = Camera(window,glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 800.0f,600.0f);
		
		vertexShader.setMat4("model", model);
		vertexShader.setMat3("NormalModel",glm::mat3(transpose(inverse(model))));
		vertexShader.setMat4("projection", projection);
		vertexShader.setMat4("view", cam.getViewMatrix());

		
		glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		unsigned int lightShaderProgram = glCreateProgram();
		Shader lightVertexShader = Shader(vertexShaderSource, GL_VERTEX_SHADER);
		lightVertexShader.AttachShaderTo(lightShaderProgram);
		Shader lightFragmentShader = Shader(lightFragmentShaderSource, GL_FRAGMENT_SHADER);
		lightFragmentShader.AttachShaderTo(lightShaderProgram);

		glm::mat4 lightModel = glm::mat4(1.0f);
		glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
		lightModel = glm::translate(lightModel, glm::vec3(1.2f, 1.0f, 2.0f));
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		lightVertexShader.useProgram();
		lightVertexShader.setMat4("model", lightModel);
		lightVertexShader.setMat4("projection", projection);
		lightVertexShader.setMat4("view", cam.getViewMatrix());
		
		glEnable(GL_DEPTH_TEST);
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			// rendering commands here
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			cam.processInput(window);

			glBindVertexArray(lightVAO);
			lightVertexShader.useProgram();
			//glm::mat4 tmpLightModel = glm::rotate(lightModel, (float)glfwGetTime()*glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			//lightVertexShader.setMat4("model", tmpLightModel);
			lightVertexShader.setMat4("view", cam.getViewMatrix());
			lightVertexShader.setMat4("projection", cam.getProjection());
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glBindVertexArray(VAO);
			vertexShader.useProgram();
			glm::mat4 tmpModel = glm::rotate(model, (float)glfwGetTime()*glm::radians(10.0f), glm::vec3(1.0f, 0.3f, 0.5f));
			//vertexShader.useProgram();
			vertexShader.setMat4("model", tmpModel);
			vertexShader.setMat4("view", cam.getViewMatrix());
			vertexShader.setMat4("projection", cam.getProjection());
			fragmentShader.setVec3("lightPos", lightPos);
			fragmentShader.setVec3("viewPos", cam.getPosition());
			vertexShader.setMat4("NormalModel", glm::mat3(transpose(inverse(tmpModel))));
			glDrawArrays(GL_TRIANGLES, 0, 36);
			
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
		return 0;
	}
};
