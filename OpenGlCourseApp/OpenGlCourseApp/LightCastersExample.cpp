#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <windows.h>

#include "Shader.cpp"
#include "Camera.h"
#include "SceneOrigin.cpp"
#include "TextureLoader.cpp"
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>

//#include "stb_image.h"
class DirectionalLightExample {
	const string vertexShaderSource = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos;"
		"layout(location = 1) in vec3 aNormal;"
		"layout (location = 2) in vec2 aTexCoords;"
		"out vec3 Normal;"
		"out vec3 FragPos;"
		"out vec2 TexCoords;"
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"void main()"
		"{"
		"gl_Position = projection * view * model * vec4(aPos, 1.0);"
		"FragPos = vec3(model * vec4(aPos, 1.0));"
		"Normal =  mat3(transpose(inverse(model))) * aNormal;"
		"TexCoords = aTexCoords;"
		"}";

	const string directionalLightFragmentShaderSource = "#version 330 core \n"
		"struct Material {"
		"sampler2D diffuse;"
		"sampler2D specular;"
		"float shininess;"
		"};"
		"struct Light {"
		"vec3 direction;"
		"vec3 ambient;"
		"vec3 diffuse;"
		"vec3 specular;"
		"};"
		"uniform Light light; "
		"out vec4 FragColor;"
		"uniform vec3 lightPos;"
		"uniform vec3 viewPos;"
		"uniform Material material;"
		"in vec3 Normal;"
		"in vec3 FragPos;"
		"in vec2 TexCoords;\n"
		"void main()"
		"{"
		"vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));"
		// diffuse
		"vec3 norm = normalize(Normal);"
		"vec3 lightDir = normalize(-light.direction);"
		"float diff = max(dot(norm, lightDir), 0.0);"
		"vec3 diffTextures = vec3(texture(material.diffuse,TexCoords));"
		"vec3 diffuse = light.diffuse * diff * diffTextures; "
		// specular
		"vec3 viewDir = normalize(viewPos - FragPos);"
		"vec3 reflectDir = reflect(-lightDir, norm);"
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);"
		"vec3 specTextures = vec3(texture(material.specular,TexCoords));"
		"vec3 specular = light.specular * spec * specTextures;"
		"vec3 result = ambient + diffuse + specular;"
		"FragColor = vec4(result, 1.0);"
		"}";

	const string pointLightFragmentShaderSource = "#version 330 core \n"
		"struct Material {"
		"sampler2D diffuse;"
		"sampler2D specular;"
		"float shininess;"
		"};"
		"struct Light {"
		"vec3 position;"
		"vec3 ambient;"
		"vec3 diffuse;"
		"vec3 specular;"
		"float constant;"
		"float linear;"
		"float quadratic;"
		"};"
		"uniform Light light; "
		"out vec4 FragColor;"
		"uniform vec3 lightPos;"
		"uniform vec3 viewPos;"
		"uniform Material material;"
		"in vec3 Normal;"
		"in vec3 FragPos;"
		"in vec2 TexCoords;\n"
		"void main()"
		"{"
		"vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));"
		// diffuse
		"vec3 norm = normalize(Normal);"
		"vec3 lightDir = normalize(light.position - FragPos);"
		"float diff = max(dot(norm, lightDir), 0.0);"
		"vec3 diffTextures = vec3(texture(material.diffuse,TexCoords));"
		"vec3 diffuse = light.diffuse * diff * diffTextures; "
		// specular
		"vec3 viewDir = normalize(viewPos - FragPos);"
		"vec3 reflectDir = reflect(-lightDir, norm);"
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);"
		"vec3 specTextures = vec3(texture(material.specular,TexCoords));"
		"vec3 specular = light.specular * spec * specTextures;"
		"float distance = length(light.position - FragPos);"
		"float attenuation = 1.0 / (light.constant + light.linear * distance +"
		"                           light.quadratic * (distance * distance));"

		"vec3 result =( ambient + diffuse + specular)*attenuation;"
		"FragColor = vec4(result, 1.0);"
		"}";

	const string flashLightFragmentShaderSource = "#version 330 core \n"
		"struct Material {"
		"sampler2D diffuse;"
		"sampler2D specular;"
		"float shininess;"
		"};"
		"struct Light {"
		"vec3 position;"
		"vec3 direction;"
		"float cutOff;"
		"vec3 ambient;"
		"vec3 diffuse;"
		"vec3 specular;"
		"float constant;"
		"float linear;"
		"float quadratic;"
		"};"
		"uniform Light light; "
		"out vec4 FragColor;"
		"uniform vec3 lightPos;"
		"uniform vec3 viewPos;"
		"uniform Material material;"
		"in vec3 Normal;"
		"in vec3 FragPos;"
		"in vec2 TexCoords;\n"
		"void main()"
		"{"
		"vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));"
		// diffuse
		"vec3 norm = normalize(Normal);"
		"vec3 lightDir = normalize(light.position - FragPos);"
		"float theta = dot(lightDir, normalize(-light.direction));"
		"float diff = max(dot(norm, lightDir), 0.0);"
		"vec3 result;"
		"if(theta > light.cutOff)"
		"{"
			"vec3 diffTextures = vec3(texture(material.diffuse,TexCoords));"
			"vec3 diffuse = light.diffuse * diff * diffTextures; "
			// specular
			"vec3 viewDir = normalize(viewPos - FragPos);"
			"vec3 reflectDir = reflect(-lightDir, norm);"
			"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);"
			"vec3 specTextures = vec3(texture(material.specular,TexCoords));"
			"vec3 specular = light.specular * spec * specTextures;"
			"float distance = length(light.position - FragPos);"
			"float attenuation = 1.0 / (light.constant + light.linear * distance +"
			"                           light.quadratic * (distance * distance));"
			"diffuse *= attenuation;"
			"specular *= attenuation;"
			"result =( ambient + diffuse + specular);"
		"}"
		"else"
		"{"
			"result = ambient;"
		"}"
		"FragColor = vec4(result, 1.0);"
		"}";
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	static void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
 	}
    void processInputForMovable(GLFWwindow *window, glm::vec3& movePosition, const glm::vec3& camDirection)
	{
		float delta = 0.001f;
		glm::vec3 res = movePosition;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			res += (camDirection * delta);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			res -= (camDirection * delta);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				res.y += delta;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				res.y -= delta;
			}
		}
		else 
		{
			glm::vec3 normal = glm::cross(camDirection, glm::vec3(0, 1, 0));
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				res -= (normal* delta);
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				res += (normal* delta);
			}
		}
		movePosition.x = res.x;
		movePosition.y = res.y;
		movePosition.z = res.z;
	}

public:


	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
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
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};
		//unsigned int indices[] = { 0, 1, 3, 3, 2, 1 };
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(VAO);

		TCHAR buffer[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, buffer, MAX_PATH);

		Shader vertexShader = Shader(vertexShaderSource, GL_VERTEX_SHADER);
		unsigned int shaderProgram = glCreateProgram();
		vertexShader.AttachShaderTo(shaderProgram);

		Shader fragmentShader = Shader(flashLightFragmentShaderSource, GL_FRAGMENT_SHADER);
		fragmentShader.AttachShaderTo(shaderProgram);
		fragmentShader.useProgram();

		TextureLoader textureLoader;

		unsigned int diffuseMap = textureLoader.loadTexture("./Textures/container2.png");
		unsigned int specularMap = textureLoader.loadTexture("./Textures/container2_specular.png");

		fragmentShader.setVec3("lightColor", glm::vec3(0.1f));
		fragmentShader.setFloat("material.shininess", 32.0f);
		fragmentShader.setInt("material.diffuse", 0);
		fragmentShader.setInt("material.specular", 1);
		fragmentShader.setVec3("light.ambient", glm::vec3(0.2f));
		fragmentShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darkened
		fragmentShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		//directional light//fragmentShader.setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		/*pointlight*/fragmentShader.setVec3("light.position", glm::vec3(1.2f, 1.0f, 2.0f));
		/*pointlight*/fragmentShader.setFloat("light.constant", 1.0f);
		/*pointlight*/fragmentShader.setFloat("light.linear", 0.09f);
		/*pointlight*/fragmentShader.setFloat("light.quadratic", 0.032f);
		
		/*flashLight*/fragmentShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		Camera cam = Camera(window, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 800.0f, 600.0f);

		vertexShader.setMat4("model", model);
		vertexShader.setMat3("TranspInvModel", glm::mat3(transpose(inverse(model))));
		vertexShader.setMat4("projection", projection);
		vertexShader.setMat4("view", cam.getViewMatrix());


		SceneOrigin origin;

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		float radius = 1.5f;

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(2.0f, 5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f, 3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f, 2.0f, -2.5f),
			glm::vec3(1.5f, 0.2f, -1.5f),
			glm::vec3(-1.3f, 1.0f, -1.5f)
		};

		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			// rendering commands here
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			cam.processInput(window);

			origin.displayOrigin(cam.getViewMatrix(), cam.getProjection());

			glBindVertexArray(VAO);
			vertexShader.useProgram();
			float angle = (float)glfwGetTime()*glm::radians(10.0f);

		
			vertexShader.setMat4("view", cam.getViewMatrix());
			vertexShader.setMat4("projection", cam.getProjection());

			fragmentShader.setVec3("viewPos", cam.getPosition());
			fragmentShader.setVec3("light.position", cam.getPosition());
			/*flashLight*/fragmentShader.setVec3("light.direction", cam.getDirection());


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMap);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, specularMap);


			float time = glfwGetTime();
			for (unsigned int i = 0; i < 10; i++)
			{
				glm::mat4 tmpModel = glm::mat4(1.0f);
				tmpModel = glm::translate(tmpModel, cubePositions[i]);
				float angle = 20.0f * (i + 1);
				tmpModel = glm::rotate(tmpModel, time*glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				vertexShader.setMat4("model", tmpModel);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
		return 0;
	}
};
