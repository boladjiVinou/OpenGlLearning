#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <windows.h>

#include "Shader.cpp"
#include "Camera.h"
#include "SceneOrigin.cpp"

//#include "stb_image.h"
class MaterialExample {
	const string vertexShaderSource = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos;"
		"layout(location = 1) in vec3 aNormal;"
		"out vec3 Normal;"
		"out vec3 FragPos;"
		"uniform mat4 model;"
		"uniform mat3 TranspInvModel;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"void main()"
		"{"
			"gl_Position = projection * view * model * vec4(aPos, 1.0);"
			"FragPos = vec3(model * vec4(aPos, 1.0));"
			"Normal = TranspInvModel * aNormal;"
		"}";

	const string fragmentShaderSource = "#version 330 core \n"

		"struct Material {"
			"vec3 ambient;"
			"vec3 diffuse;"
			"vec3 specular;"
			"float shininess;"
		"};"
		"struct Light {"
			"vec3 position;"
			"vec3 ambient;"
			"vec3 diffuse;"
			"vec3 specular;"
		"};"
		"uniform Light light; "
		"out vec4 FragColor;"
		"uniform vec3 objectColor;"
		"uniform vec3 lightPos;"
		"uniform vec3 viewPos;"
		"uniform Material material;"
		"in vec3 Normal;"
		"in vec3 FragPos;"
		"void main()"
		"{"
			"vec3 ambient = light.ambient * material.ambient;"
			// diffuse
			"vec3 norm = normalize(Normal);"
			"vec3 lightDir = normalize(lightPos - FragPos);"
			"float diff = max(dot(norm, lightDir), 0.0);"
			"vec3 diffuse = light.diffuse * (diff * material.diffuse);"
			// specular
			"vec3 viewDir = normalize(viewPos - FragPos);"
			"vec3 reflectDir = reflect(-lightDir, norm);"
			"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);"
			"vec3 specular = light.specular * (spec * material.specular);"
			"vec3 result = ambient + diffuse + specular;"
			"FragColor = vec4(result, 1.0);"
		"}";
	const string lightFragmentShaderSource = "#version 330 core\n"
		"struct Light {"
			"vec3 position;"
			"vec3 ambient;"
			"vec3 diffuse;"
			"vec3 specular;"
		"};"
		"uniform Light light; "
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4( light.ambient + light.diffuse + light.specular,1.0);\n"
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
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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

		TCHAR buffer[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, buffer, MAX_PATH);

		Shader vertexShader = Shader(vertexShaderSource, GL_VERTEX_SHADER);
		unsigned int shaderProgram = glCreateProgram();
		vertexShader.AttachShaderTo(shaderProgram);

		Shader fragmentShader = Shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
		fragmentShader.AttachShaderTo(shaderProgram);
		fragmentShader.useProgram();
		fragmentShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));//objectColor
		fragmentShader.setVec3("lightColor", glm::vec3(0.1f, 0.1f, 0.1f));
		fragmentShader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		fragmentShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		fragmentShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		fragmentShader.setFloat("material.shininess",32.0f);
		fragmentShader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		fragmentShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darkened
		fragmentShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		



		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		Camera cam = Camera(window, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 800.0f, 600.0f);

		vertexShader.setMat4("model", model);
		vertexShader.setMat3("TranspInvModel", glm::mat3(transpose(inverse(model))));
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

		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.1f));

		lightVertexShader.useProgram();
		lightVertexShader.setMat4("model", lightModel);
		lightVertexShader.setMat4("projection", projection);
		lightVertexShader.setMat4("view", cam.getViewMatrix());


		lightFragmentShader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		lightFragmentShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darkened
		lightFragmentShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);



		SceneOrigin origin;

		glEnable(GL_DEPTH_TEST);
		float radius = 1.5f;
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			// rendering commands here
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			cam.processInput(window);

			origin.displayOrigin(cam.getViewMatrix(), cam.getProjection());

			glm::vec3 lightColor;
			lightColor.x = sin(glfwGetTime() * 2.0f);
			lightColor.y = sin(glfwGetTime() * 0.7f);
			lightColor.z = sin(glfwGetTime() * 1.3f);
			glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
			glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);


			glBindVertexArray(lightVAO);
			lightVertexShader.useProgram();
			//glm::mat4 tmpLightModel = glm::rotate(lightModel, (float)glfwGetTime()*glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			//lightVertexShader.setMat4("model", tmpLightModel);
			lightVertexShader.setMat4("view", cam.getViewMatrix());
			lightVertexShader.setMat4("projection", cam.getProjection());
			lightFragmentShader.setVec3("light.ambient", ambientColor);
			lightFragmentShader.setVec3("light.diffuse", diffuseColor);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glBindVertexArray(VAO);
			vertexShader.useProgram();
			float angle = (float)glfwGetTime()*glm::radians(10.0f);
			
			glm::mat4 tmpModel = glm::translate(model, glm::vec3(-radius*cos(angle) + lightPos.x, lightPos.y/2.0f +0.3f, -radius*sin(angle)+lightPos.z));
			vertexShader.setMat4("model", tmpModel);
			vertexShader.setMat4("view", cam.getViewMatrix());
			vertexShader.setMat4("projection", cam.getProjection());
			fragmentShader.setVec3("lightPos", lightPos);
			fragmentShader.setVec3("viewPos", cam.getPosition());
			
			fragmentShader.setVec3("light.ambient", ambientColor);
			fragmentShader.setVec3("light.diffuse", diffuseColor);
			vertexShader.setMat4("TranspInvModel", glm::mat3(transpose(inverse(tmpModel))));
			glDrawArrays(GL_TRIANGLES, 0, 36);


			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
		return 0;
	}
};
