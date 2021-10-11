#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"
#include "SceneOrigin.h"

//#include "stb_image.h"
class ColorsExercice1 {
	const string vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"out vec3 Normal;"
		"out vec3 FragPos;"
		"uniform mat4 model;\n"
		"uniform mat3 TranspInvModel;"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
		"	FragPos = vec3(model * vec4(aPos, 1.0));"
		"   Normal =TranspInvModel*aNormal; "
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
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);"
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


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);

public:

	int run();
};
