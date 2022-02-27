#include "LightCastersExample.h";

void LightCastersExample::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void LightCastersExample::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void LightCastersExample::processInputForMovable(GLFWwindow *window, glm::vec3& movePosition, const glm::vec3& camDirection)
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

int  LightCastersExample::run()
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

	Shader vertexShader = Shader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int shaderProgram = glCreateProgram();
	vertexShader.AttachShaderTo(shaderProgram);

	Shader fragmentShader = Shader(pointLightFragmentShaderSource, GL_FRAGMENT_SHADER);
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
	//directional light// fragmentShader.setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	/*pointlight*/fragmentShader.setVec3("light.position", glm::vec3(1.2f, 1.0f, 2.0f));
	/*pointlight*/fragmentShader.setFloat("light.constant", 1.0f);
	/*pointlight*/fragmentShader.setFloat("light.linear", 0.09f);
	/*pointlight*/fragmentShader.setFloat("light.quadratic", 0.032f);

	/*flashLight*///fragmentShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));

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
		/*flashLight*///fragmentShader.setVec3("light.direction", cam.getDirection());


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
			vertexShader.setMat3("invTransNormal", glm::transpose(glm::inverse(glm::mat3(tmpModel))));
			vertexShader.setMat4("model", tmpModel);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}




int LightCastersExample::runMultipleLight()
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

	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);



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

	Shader fragmentShader = Shader(multiLightFragmentShaderSource, GL_FRAGMENT_SHADER);
	fragmentShader.AttachShaderTo(shaderProgram);
	fragmentShader.useProgram();

	TextureLoader textureLoader;

	unsigned int diffuseMap = textureLoader.loadTexture("./Textures/container2.png");
	unsigned int specularMap = textureLoader.loadTexture("./Textures/container2_specular.png");

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};

	fragmentShader.setVec3("lightColor", glm::vec3(0.1f));
	fragmentShader.setFloat("material.shininess", 32.0f);
	fragmentShader.setInt("material.diffuse", 0);
	fragmentShader.setInt("material.specular", 1);
	fragmentShader.setVec3("dirLight.ambient", glm::vec3(0.2f));
	fragmentShader.setVec3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darkened
	fragmentShader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	fragmentShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

	for (int i = 0; i < 4; ++i)
	{
		string index = std::to_string(i);
		fragmentShader.setVec3("pointLights[" + index + "].position", pointLightPositions[i]);
		fragmentShader.setFloat("pointLights[" + index + "].constant", 1.0f);
		fragmentShader.setFloat("pointLights[" + index + "].linear", 0.09f);
		fragmentShader.setFloat("pointLights[" + index + "].quadratic", 0.032f);
		fragmentShader.setVec3("pointLights[" + index + "].ambient", glm::vec3(0.2f));
		fragmentShader.setVec3("pointLights[" + index + "].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		fragmentShader.setVec3("pointLights[" + index + "].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	}




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
			vertexShader.setMat3("invTransNormal", glm::transpose(glm::inverse(glm::mat3(tmpModel))));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

int LightCastersExample::desert()
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

	glClearColor(0.7f, 0.35f, 0.0f, 1.0f);



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

	unsigned int VAO, lightVAO;
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

	Shader fragmentShader = Shader(multiLightFragmentShaderSource, GL_FRAGMENT_SHADER);
	fragmentShader.AttachShaderTo(shaderProgram);
	fragmentShader.useProgram();

	TextureLoader textureLoader;

	unsigned int diffuseMap = textureLoader.loadTexture("./Textures/container2.png");
	unsigned int specularMap = textureLoader.loadTexture("./Textures/container2_specular.png");

	Light pointLights[4];
	pointLights[0].position = glm::vec3(0.7f, 0.2f, 2.0f);
	pointLights[1].position = glm::vec3(2.3f, -3.3f, -4.0f);
	pointLights[2].position = glm::vec3(-4.0f, 2.0f, -12.0f);
	pointLights[3].position = glm::vec3(0.0f, 0.0f, -3.0f);

	fragmentShader.setVec3("lightColor", glm::vec3(0.1f));
	fragmentShader.setFloat("material.shininess", 32.0f);
	fragmentShader.setInt("material.diffuse", 0);
	fragmentShader.setInt("material.specular", 1);
	fragmentShader.setVec3("dirLight.ambient", glm::vec3(0.2f));
	fragmentShader.setVec3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darkened
	fragmentShader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	fragmentShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	for (int i = 0; i < 4; ++i)
	{
		string index = std::to_string(i);
		pointLights[i].constant = constant;
		pointLights[i].linear = linear;
		pointLights[i].quadratic = quadratic;
		fragmentShader.setVec3("pointLights[" + index + "].position", pointLights[i].position);
		fragmentShader.setFloat("pointLights[" + index + "].constant", pointLights[i].constant);
		fragmentShader.setFloat("pointLights[" + index + "].linear", pointLights[i].linear);
		fragmentShader.setFloat("pointLights[" + index + "].quadratic", pointLights[i].quadratic);

		pointLights[i].ambient = glm::vec3(0.2f);
		switch (i)
		{
		case 0:
			pointLights[i].diffuse = glm::vec3(0.5f, 0.0f, 0.0f);
			pointLights[i].specular = glm::vec3(1.0f, 0.0f, 0.0f);
			break;
		case 1:
			pointLights[i].diffuse = glm::vec3(0.0f, 0.5f, 0.0f);
			pointLights[i].specular = glm::vec3(0.0f, 1.0f, 0.0f);
			break;
		case 2:
			pointLights[i].diffuse = glm::vec3(0.0f, 0.0f, 0.5f);
			pointLights[i].specular = glm::vec3(0.0f, 0.0f, 1.0f);
			break;
		case 3:
			pointLights[i].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
			pointLights[i].specular = glm::vec3(1.0f, 1.0f, 1.0f);
			break;
		}


		fragmentShader.setVec3("pointLights[" + index + "].ambient", pointLights[i].ambient);
		fragmentShader.setVec3("pointLights[" + index + "].diffuse", pointLights[i].diffuse);
		fragmentShader.setVec3("pointLights[" + index + "].specular", pointLights[i].specular);
	}




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


	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	unsigned int lightShaderProgram = glCreateProgram();
	Shader lightVertexShader = Shader(vertexShaderSource, GL_VERTEX_SHADER);
	lightVertexShader.AttachShaderTo(lightShaderProgram);
	Shader lightFragmentShader = Shader(lightFragmentShaderSource, GL_FRAGMENT_SHADER);
	lightFragmentShader.AttachShaderTo(lightShaderProgram);

	glm::mat4 lightModel = glm::mat4(1.0f);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
	glm::vec3 lightScale = glm::vec3(0.1f);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// rendering commands here
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cam.processInput(window);

		origin.displayOrigin(cam.getViewMatrix(), cam.getProjection());

		glBindVertexArray(lightVAO);
		lightVertexShader.useProgram();

		lightVertexShader.setMat4("projection", cam.getProjection());
		lightVertexShader.setMat4("view", cam.getViewMatrix());

		for (int i = 0; i < 4; ++i)
		{
			glm::mat4 tmpLightModel = lightModel;
			tmpLightModel = glm::translate(tmpLightModel, pointLights[i].position);
			tmpLightModel = glm::scale(tmpLightModel, lightScale);
			lightVertexShader.setMat4("model", tmpLightModel);
			vertexShader.setMat3("TranspInvModel", transpose(inverse(glm::mat3(tmpLightModel))));
			lightFragmentShader.setVec3("light.position", pointLights[i].position);
			lightFragmentShader.setVec3("light.ambient", pointLights[i].ambient);
			lightFragmentShader.setVec3("light.diffuse", pointLights[i].diffuse);
			lightFragmentShader.setVec3("light.specular", pointLights[i].specular);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(VAO);
		vertexShader.useProgram();
		float angle = (float)glfwGetTime()*glm::radians(10.0f);


		vertexShader.setMat4("view", cam.getViewMatrix());
		vertexShader.setMat4("projection", cam.getProjection());

		fragmentShader.setVec3("viewPos", cam.getPosition());


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
			vertexShader.setMat3("invTransNormal", glm::transpose(glm::inverse(glm::mat3(tmpModel))));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

int LightCastersExample::horror()
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

	unsigned int VAO, lightVAO;
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

	Shader fragmentShader = Shader(multiLightFragmentShaderSource, GL_FRAGMENT_SHADER);
	fragmentShader.AttachShaderTo(shaderProgram);
	fragmentShader.useProgram();

	TextureLoader textureLoader;

	unsigned int diffuseMap = textureLoader.loadTexture("./Textures/container2.png");
	unsigned int specularMap = textureLoader.loadTexture("./Textures/container2_specular.png");

	Light pointLights[4];
	pointLights[0].position = glm::vec3(0.7f, 0.2f, 2.0f);
	pointLights[1].position = glm::vec3(2.3f, -3.3f, -4.0f);
	pointLights[2].position = glm::vec3(-4.0f, 2.0f, -12.0f);
	pointLights[3].position = glm::vec3(0.0f, 0.0f, -3.0f);

	fragmentShader.setVec3("lightColor", glm::vec3(0.1f));
	fragmentShader.setFloat("material.shininess", 32.0f);
	fragmentShader.setInt("material.diffuse", 0);
	fragmentShader.setInt("material.specular", 1);
	fragmentShader.setVec3("dirLight.ambient", glm::vec3(0.0f));
	fragmentShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f)); // darkened
	fragmentShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));
	fragmentShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	for (int i = 0; i < 4; ++i)
	{
		string index = std::to_string(i);
		pointLights[i].constant = constant;
		pointLights[i].linear = linear;
		pointLights[i].quadratic = quadratic;
		fragmentShader.setVec3("pointLights[" + index + "].position", pointLights[i].position);
		fragmentShader.setFloat("pointLights[" + index + "].constant", pointLights[i].constant);
		fragmentShader.setFloat("pointLights[" + index + "].linear", pointLights[i].linear);
		fragmentShader.setFloat("pointLights[" + index + "].quadratic", pointLights[i].quadratic);

		pointLights[i].ambient = glm::vec3(0.2f);
		switch (i)
		{
		case 0:
			pointLights[i].diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
			pointLights[i].specular = glm::vec3(0.0f, 0.0f, 0.0f);
			pointLights[i].ambient = glm::vec3(0.0f);
			break;
		case 1:
			pointLights[i].diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
			pointLights[i].specular = glm::vec3(0.0f, 0.0f, 0.0f);
			pointLights[i].ambient = glm::vec3(0.0f);
			break;
		case 2:
			pointLights[i].diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
			pointLights[i].specular = glm::vec3(0.0f, 0.0f, 0.0f);
			pointLights[i].ambient = glm::vec3(0.0f);
			break;
		case 3:
			pointLights[i].diffuse = glm::vec3(0.5f, 0.0f, 0.0f);
			pointLights[i].specular = glm::vec3(1.0f, 0.0f, 0.0f);
			break;
		}


		fragmentShader.setVec3("pointLights[" + index + "].ambient", pointLights[i].ambient);
		fragmentShader.setVec3("pointLights[" + index + "].diffuse", pointLights[i].diffuse);
		fragmentShader.setVec3("pointLights[" + index + "].specular", pointLights[i].specular);
	}




	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Camera cam = Camera(window, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 800.0f, 600.0f);


	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	unsigned int lightShaderProgram = glCreateProgram();
	Shader lightVertexShader = Shader(vertexShaderSource, GL_VERTEX_SHADER);
	lightVertexShader.AttachShaderTo(lightShaderProgram);
	Shader lightFragmentShader = Shader(lightFragmentShaderSource, GL_FRAGMENT_SHADER);
	lightFragmentShader.AttachShaderTo(lightShaderProgram);

	glm::mat4 lightModel = glm::mat4(1.0f);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
	glm::vec3 lightScale = glm::vec3(0.1f);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// rendering commands here
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cam.processInput(window);

		origin.displayOrigin(cam.getViewMatrix(), cam.getProjection());

		glBindVertexArray(lightVAO);
		lightVertexShader.useProgram();

		lightVertexShader.setMat4("projection", cam.getProjection());
		lightVertexShader.setMat4("view", cam.getViewMatrix());

		for (int i = 0; i < 4; ++i)
		{
			glm::mat4 tmpLightModel = lightModel;
			tmpLightModel = glm::translate(tmpLightModel, pointLights[i].position);
			tmpLightModel = glm::scale(tmpLightModel, lightScale);
			lightVertexShader.setMat4("model", tmpLightModel);
			vertexShader.setMat3("TranspInvModel", transpose(inverse(glm::mat3(tmpLightModel))));
			lightFragmentShader.setVec3("light.position", pointLights[i].position);
			lightFragmentShader.setVec3("light.ambient", pointLights[i].ambient);
			lightFragmentShader.setVec3("light.diffuse", pointLights[i].diffuse);
			lightFragmentShader.setVec3("light.specular", pointLights[i].specular);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(VAO);
		vertexShader.useProgram();
		float angle = (float)glfwGetTime()*glm::radians(10.0f);


		vertexShader.setMat4("view", cam.getViewMatrix());
		vertexShader.setMat4("projection", cam.getProjection());

		fragmentShader.setVec3("viewPos", cam.getPosition());


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
			vertexShader.setMat3("invTransNormal", glm::transpose(glm::inverse(glm::mat3(tmpModel))));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}


int LightCastersExample::bioChemicalLab()
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

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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

	unsigned int VAO, lightVAO;
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

	Shader fragmentShader = Shader(multiLightFragmentShaderSource, GL_FRAGMENT_SHADER);
	fragmentShader.AttachShaderTo(shaderProgram);
	fragmentShader.useProgram();

	TextureLoader textureLoader;

	unsigned int diffuseMap = textureLoader.loadTexture("./Textures/container2.png");
	unsigned int specularMap = textureLoader.loadTexture("./Textures/container2_specular.png");

	Light pointLights[4];
	pointLights[0].position = glm::vec3(0.7f, 0.2f, 2.0f);
	pointLights[1].position = glm::vec3(2.3f, -3.3f, -4.0f);
	pointLights[2].position = glm::vec3(-4.0f, 2.0f, -12.0f);
	pointLights[3].position = glm::vec3(0.0f, 0.0f, -3.0f);

	fragmentShader.setVec3("lightColor", glm::vec3(0.1f));
	fragmentShader.setFloat("material.shininess", 32.0f);
	fragmentShader.setInt("material.diffuse", 0);
	fragmentShader.setInt("material.specular", 1);
	fragmentShader.setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.0f));
	fragmentShader.setVec3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.0f)); // darkened
	fragmentShader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 0.0f));
	fragmentShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	for (int i = 0; i < 4; ++i)
	{
		string index = std::to_string(i);
		pointLights[i].constant = constant;
		pointLights[i].linear = linear;
		pointLights[i].quadratic = quadratic;
		fragmentShader.setVec3("pointLights[" + index + "].position", pointLights[i].position);
		fragmentShader.setFloat("pointLights[" + index + "].constant", pointLights[i].constant);
		fragmentShader.setFloat("pointLights[" + index + "].linear", pointLights[i].linear);
		fragmentShader.setFloat("pointLights[" + index + "].quadratic", pointLights[i].quadratic);

		pointLights[i].ambient = glm::vec3(0.2f);
		switch (i)
		{
		case 0:
			pointLights[i].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
			pointLights[i].specular = glm::vec3(1.0f, 1.0f, 1.0f);
			break;
		case 1:
			pointLights[i].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
			pointLights[i].specular = glm::vec3(1.0f, 1.0f, 1.0f);
			break;
		case 2:
			pointLights[i].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
			pointLights[i].specular = glm::vec3(1.0f, 1.0f, 1.0f);
			break;
		case 3:
			pointLights[i].diffuse = glm::vec3(0.0f, 0.5f, 0.0f);
			pointLights[i].specular = glm::vec3(0.0f, 1.0f, 0.0f);
			break;
		}


		fragmentShader.setVec3("pointLights[" + index + "].ambient", pointLights[i].ambient);
		fragmentShader.setVec3("pointLights[" + index + "].diffuse", pointLights[i].diffuse);
		fragmentShader.setVec3("pointLights[" + index + "].specular", pointLights[i].specular);
	}




	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Camera cam = Camera(window, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 800.0f, 600.0f);


	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	unsigned int lightShaderProgram = glCreateProgram();
	Shader lightVertexShader = Shader(vertexShaderSource, GL_VERTEX_SHADER);
	lightVertexShader.AttachShaderTo(lightShaderProgram);
	Shader lightFragmentShader = Shader(lightFragmentShaderSource, GL_FRAGMENT_SHADER);
	lightFragmentShader.AttachShaderTo(lightShaderProgram);

	glm::mat4 lightModel = glm::mat4(1.0f);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
	glm::vec3 lightScale = glm::vec3(0.1f);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// rendering commands here
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cam.processInput(window);

		origin.displayOrigin(cam.getViewMatrix(), cam.getProjection());

		glBindVertexArray(lightVAO);
		lightVertexShader.useProgram();

		lightVertexShader.setMat4("projection", cam.getProjection());
		lightVertexShader.setMat4("view", cam.getViewMatrix());

		for (int i = 0; i < 4; ++i)
		{
			glm::mat4 tmpLightModel = lightModel;
			tmpLightModel = glm::translate(tmpLightModel, pointLights[i].position);
			tmpLightModel = glm::scale(tmpLightModel, lightScale);
			lightVertexShader.setMat4("model", tmpLightModel);
			vertexShader.setMat3("TranspInvModel", transpose(inverse(glm::mat3(tmpLightModel))));
			lightFragmentShader.setVec3("light.position", pointLights[i].position);
			lightFragmentShader.setVec3("light.ambient", pointLights[i].ambient);
			lightFragmentShader.setVec3("light.diffuse", pointLights[i].diffuse);
			lightFragmentShader.setVec3("light.specular", pointLights[i].specular);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(VAO);
		vertexShader.useProgram();
		float angle = (float)glfwGetTime()*glm::radians(10.0f);


		vertexShader.setMat4("view", cam.getViewMatrix());
		vertexShader.setMat4("projection", cam.getProjection());

		fragmentShader.setVec3("viewPos", cam.getPosition());


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
			vertexShader.setMat3("invTransNormal", glm::transpose(glm::inverse(glm::mat3(tmpModel))));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
