#include "MaterialExample.h"

void MaterialExample::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void MaterialExample::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int MaterialExample::run()
{
	Material materials[24];
	/*emerald*/					materials[0].ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f); materials[0].diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);	materials[0].specular = glm::vec3(0.633f, 0.727811f, 0.633f); materials[0].shininess = 0.6f;
	/*jade*/					materials[1].ambient = glm::vec3(0.135f, 0.2225f, 0.1575f); materials[1].diffuse = glm::vec3(0.54f, 0.89f, 0.63f); materials[1].specular = glm::vec3(0.316228f, 0.316228f, 0.316228f); materials[1].shininess = 0.1f;
	/*obsidian	*/			materials[2].ambient = glm::vec3(0.05375f, 0.05f, 0.06625f); materials[2].diffuse = glm::vec3(0.18275f, 0.17f, 0.22525f); materials[2].specular = glm::vec3(0.332741f, 0.328634f, 0.346435f); materials[2].shininess = 0.3f;
	/*pearl		*/			materials[3].ambient = glm::vec3(0.25f, 0.20725f, 0.20725f); materials[3].diffuse = glm::vec3(1.0f, 0.829f, 0.829f); materials[3].specular = glm::vec3(0.296648f, 0.296648f, 0.296648f); materials[3].shininess = 0.088f;
	/*ruby	*/				materials[4].ambient = glm::vec3(0.1745f, 0.01175f, 0.01175f); materials[4].diffuse = glm::vec3(0.61424f, 0.04136f, 0.04136f); materials[4].specular = glm::vec3(0.727811f, 0.626959f, 0.626959f); materials[4].shininess = 0.6f;
	/*turquoise	*/			materials[5].ambient = glm::vec3(0.1f, 0.18725f, 0.1745f); materials[5].diffuse = glm::vec3(0.396f, 0.74151f, 0.69102f); materials[5].specular = glm::vec3(0.297254f, 0.30829f, 0.306678f); materials[5].shininess = 0.1f;
	/*brass	*/				materials[6].ambient = glm::vec3(0.329412f, 0.223529f, 0.027451f); materials[6].diffuse = glm::vec3(0.780392f, 0.568627f, 0.113725f); materials[6].specular = glm::vec3(0.992157f, 0.941176f, 0.807843f); materials[6].shininess = 0.21794872f;
	/*bronze*/					materials[7].ambient = glm::vec3(0.2125f, 0.1275f, 0.054f); materials[7].diffuse = glm::vec3(0.714f, 0.4284f, 0.18144f); materials[7].specular = glm::vec3(0.393548f, 0.271906f, 0.166721f); materials[7].shininess = 0.2f;
	/*chrome	*/				materials[8].ambient = glm::vec3(0.25f, 0.25f, 0.25f); materials[8].diffuse = glm::vec3(0.4f, 0.4f, 0.4f); materials[8].specular = glm::vec3(0.774597f, 0.774597f, 0.774597f); materials[8].shininess = 0.6f;
	/*copper	*/				materials[9].ambient = glm::vec3(0.19125f, 0.0735f, 0.0225f);	materials[9].diffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f); materials[9].specular = glm::vec3(0.256777f, 0.137622f, 0.086014f); materials[9].shininess = 0.1f;
	/*gold	*/				materials[10].ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f); materials[10].diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f); materials[10].specular = glm::vec3(0.628281f, 0.555802f, 0.366065f); materials[10].shininess = 0.4f;;
	/*silver		*/			materials[11].ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f); materials[11].diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f); materials[11].specular = glm::vec3(0.508273f, 0.508273f, 0.508273f); materials[11].shininess = 0.4f;
	/*black plastic	*/		materials[12].ambient = glm::vec3(0.0f, 0.0f, 0.0f); materials[12].diffuse = glm::vec3(0.01f, 0.01f, 0.01f); materials[12].specular = glm::vec3(0.50f, 0.50f, 0.50f); materials[12].shininess = .25f;
	/*cyan plastic	*/		materials[13].ambient = glm::vec3(0.0f, 0.1f, 0.06f); materials[13].diffuse = glm::vec3(0.0f, 0.50980392f, 0.50980392f); materials[13].specular = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f); materials[13].shininess = .25f;
	/*green plastic*/			materials[14].ambient = glm::vec3(0.0f, 0.0f, 0.0f); materials[14].diffuse = glm::vec3(0.1f, 0.35f, 0.1f); materials[14].specular = glm::vec3(0.45f, 0.55f, 0.45f); materials[14].shininess = .25f;
	/*red plastic	*/			materials[15].ambient = glm::vec3(0.0f, 0.0f, 0.0f); materials[15].diffuse = glm::vec3(0.5f, 0.0f, 0.0f); materials[15].specular = glm::vec3(0.7f, 0.6f, 0.6f); materials[15].shininess = .25f;
	/*white plastic	*/		materials[16].ambient = glm::vec3(0.0f, 0.0f, 0.0f);	materials[16].diffuse = glm::vec3(0.55f, 0.55f, 0.55f); materials[16].specular = glm::vec3(0.70f, 0.70f, 0.70f); materials[16].shininess = .25f;
	/*yellow plastic*/			materials[17].ambient = glm::vec3(0.0f, 0.0f, 0.0f);	materials[17].diffuse = glm::vec3(0.5f, 0.5f, 0.0f); materials[17].specular = glm::vec3(0.60f, 0.60f, 0.50f); materials[17].shininess = .25f;
	/*black rubber*/			materials[18].ambient = glm::vec3(0.02f, 0.02f, 0.02f); materials[18].diffuse = glm::vec3(0.01f, 0.01f, 0.01f); materials[18].specular = glm::vec3(0.4f, 0.4f, 0.4f); materials[18].shininess = .078125f;
	/*cyan rubber	*/			materials[19].ambient = glm::vec3(0.0f, 0.05f, 0.05f); materials[19].diffuse = glm::vec3(0.4f, 0.5f, 0.5f); materials[19].specular = glm::vec3(0.04f, 0.7f, 0.7f); materials[19].shininess = .078125f;
	/*green rubber	*/		materials[20].ambient = glm::vec3(0.0f, 0.05f, 0.0f); materials[20].diffuse = glm::vec3(0.4f, 0.5f, 0.4f); materials[20].specular = glm::vec3(0.04f, 0.7f, 0.04f); materials[20].shininess = .078125f;
	/*red rubber	*/			materials[21].ambient = glm::vec3(0.05f, 0.0f, 0.0f);	materials[21].diffuse = glm::vec3(0.5f, 0.4f, 0.4f); materials[21].specular = glm::vec3(0.7f, 0.04f, 0.04f); materials[21].shininess = .078125f;
	/*white rubber	*/		materials[22].ambient = glm::vec3(0.05f, 0.05f, 0.05f);	materials[22].diffuse = glm::vec3(0.5f, 0.5f, 0.5f); materials[22].specular = glm::vec3(0.7f, 0.7f, 0.7f); materials[22].shininess = .078125f;
	/*yellow rubber	*/		materials[23].ambient = glm::vec3(0.05f, 0.05f, 0.0f);	materials[23].diffuse = glm::vec3(0.5f, 0.5f, 0.4f); materials[23].specular = glm::vec3(0.7f, 0.7f, 0.04f); materials[23].shininess = .078125f;

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
	fragmentShader.setVec3("lightColor", glm::vec3(0.1f));
	Material material = materials[rand() % 24];//
	fragmentShader.setVec3("material.ambient", material.ambient);
	fragmentShader.setVec3("material.diffuse", material.diffuse);
	fragmentShader.setVec3("material.specular", material.specular);
	fragmentShader.setFloat("material.shininess", material.shininess);
	fragmentShader.setVec3("light.ambient", glm::vec3(1.0f));
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

		glm::mat4 tmpModel = glm::translate(model, glm::vec3(-radius * cos(angle) + lightPos.x, lightPos.y / 2.0f + 0.3f, -radius * sin(angle) + lightPos.z));
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
