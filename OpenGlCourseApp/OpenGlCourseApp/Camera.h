#pragma once
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
class Camera {
private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 target;
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::mat4 lookAt;
	float far = 0;
	float deltaTime = 0.0f; // Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	void updateLookat();
	glm::mat4 myLookat();
	
public:
	static float lastX;
	static float lastY;
	static bool firstMouse;
	static float yaw, pitch;
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float far);
	void processInput(GLFWwindow *window);
	glm::mat4 getViewMatrix();
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void updateRotation();
};