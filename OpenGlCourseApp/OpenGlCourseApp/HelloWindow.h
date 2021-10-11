#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class HelloWindow {
	static	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);

public:
	static int run();
};

