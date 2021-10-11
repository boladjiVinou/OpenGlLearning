#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <windows.h>

#include "Shader.h"
#include "Camera.h"
#include "SceneOrigin.h"
#include "TextureLoader.h"

//#include "stb_image.h"
class LightingMapsExample {
	const string vertexShaderSource = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos;"
		"layout(location = 1) in vec3 aNormal;"
		"layout (location = 2) in vec2 aTexCoords;"
		"out vec3 Normal;"
		"out vec3 FragPos;"
		"out vec2 TexCoords;"
		"uniform mat4 model;"
		"uniform mat3 TranspInvModel;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"void main()"
		"{"
		"gl_Position = projection * view * model * vec4(aPos, 1.0);"
		"FragPos = vec3(model * vec4(aPos, 1.0));"
		"Normal = TranspInvModel * aNormal;"
		"TexCoords = aTexCoords;"
		"}";

	const string fragmentShaderSource = "#version 330 core \n"
		"struct Material {"
		"sampler2D diffuse;"
		"sampler2D specular;"
		"float shininess;"
		"sampler2D emission;"
		"};"
		"struct Light {"
		"vec3 position;"
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
		"vec3 lightDir = normalize(lightPos - FragPos);"
		"float diff = max(dot(norm, lightDir), 0.0);"
		"vec3 diffTextures = vec3(texture(material.diffuse,TexCoords));"
		"vec3 diffuse = light.diffuse * diff * diffTextures; "
		// specular
		"vec3 viewDir = normalize(viewPos - FragPos);"
		"vec3 reflectDir = reflect(-lightDir, norm);"
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);"
		"vec3 specTextures = vec3(texture(material.specular,TexCoords));"
		/*"if(specTextures.x > 0){"//wood steel inversion
		"specTextures.x = 0;"
		"}"
		"else{"
		"specTextures.x = diffTextures.x;"
		"}"
		"if(specTextures.y  > 0){"
		"specTextures.y = 0;"
		"}"
		"else{"
		"specTextures.y = diffTextures.y;"
		"}"
		"if(specTextures.z > 0){"
		"specTextures.z = 0;"
		"}"
		"else{"
		"specTextures.z = diffTextures.z;"
		"}"*/
		"vec3 specular = light.specular * spec * specTextures;"
		/*"vec3 emission =  vec3(texture(material.emission, TexCoords));"*/ //emission exercice
		"vec3 result = ambient + diffuse + specular;"
		"FragColor = vec4(result, 1.0);"// vec4(result, 1.0);
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


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);

public:


	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
	int run();
};
