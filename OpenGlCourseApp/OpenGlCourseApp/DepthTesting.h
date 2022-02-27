#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include "Shader.h"
#include "Camera.h"
class DepthTesting 
{
private:
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
	const string depthTestinFragShaderSource = "#version 330 core\n"
		"out vec4 FragColor;"
		"float near = 0.1;"
		"float far = 100.0;"
		"float LinearizeDepth(float depth);"
		"void main()"
		"{"
			"float depth = LinearizeDepth(gl_FragCoord.z) / far;"
			"FragColor = vec4(vec3(depth), 1.0);"
		"}"
		"float LinearizeDepth(float depth)"
		"{"
			"float z = depth * 2.0 - 1.0;"
			"return (2.0 * near * far) / (far + near - z * (far - near));"
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
	int run();
};