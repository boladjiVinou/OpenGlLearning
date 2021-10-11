#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <windows.h>

#include "Shader.h"
#include "Camera.h"
#include "SceneOrigin.h"
#include "TextureLoader.h"
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>

class LightCastersExample {
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
		"uniform mat3 invTransNormal;"
		"void main()"
		"{"
		"gl_Position = projection * view * model * vec4(aPos, 1.0);"
		"FragPos = vec3(model * vec4(aPos, 1.0));"
		"Normal =  invTransNormal * aNormal;"
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

	const string multiLightFragmentShaderSource = "#version 330 core \n"
		"#define NR_POINT_LIGHTS 4 \n"
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

		"uniform Light dirLight; "
		"uniform Light pointLights[NR_POINT_LIGHTS]; "

		"out vec4 FragColor;"
		"uniform vec3 lightPos;"
		"uniform vec3 viewPos;"
		"uniform Material material;"
		"in vec3 Normal;"
		"in vec3 FragPos;"
		"in vec2 TexCoords;\n"

		"vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir);"
		"vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);"
		"void main()"
		"{"
		// properties
		"vec3 norm = normalize(Normal);"
		"vec3 viewDir = normalize(viewPos - FragPos);"
		// phase 1: Directional lighting
		"vec3 result = CalcDirLight(dirLight, norm, viewDir);"
		// phase 2: Point lights
		"for (int i = 0; i < NR_POINT_LIGHTS; i++)"
		"{"
		"result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);"
		"}"
		// phase 3: Spot light
		//result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
		"FragColor = vec4(result, 1.0);"
		"}"

		"vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir)"
		"{"
		"vec3 lightDir = normalize(-light.direction);"
		// diffuse shading
		"float diff = max(dot(normal, lightDir), 0.0);"
		// specular shading
		"vec3 reflectDir = reflect(-lightDir, normal);"
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);"
		// combine results
		"vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));"
		"vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));"
		"vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));"
		"return (ambient + diffuse + specular);"
		"}"

		"vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)"
		"{"
		"vec3 lightDir = normalize(light.position - fragPos);"
		// diffuse shading
		"float diff = max(dot(normal, lightDir), 0.0);"
		// specular shading
		"vec3 reflectDir = reflect(-lightDir, normal);"
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);"
		// attenuation
		"float distance = length(light.position - fragPos);"
		"float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));"
		// combine results
		"vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));"
		"vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));"
		"vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));"
		"ambient *= attenuation;"
		"diffuse *= attenuation;"
		"specular *= attenuation;"
		"return (ambient + diffuse + specular);"
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
	void processInputForMovable(GLFWwindow *window, glm::vec3& movePosition, const glm::vec3& camDirection);

public:


	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
	struct Light
	{
		glm::vec3 position;
		glm::vec3 direction;
		float cutOff;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant = 0;
		float linear = 0;
		float quadratic = 0;
		float cutoff = 0;
	};
	int run();
	int runMultipleLight();
	int desert();
	int horror();
	int bioChemicalLab();
};
