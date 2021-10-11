#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"
#include "SceneOrigin.h"

//#include "stb_image.h"
class SceneOriginTest {

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);

public:

	int run();
};
