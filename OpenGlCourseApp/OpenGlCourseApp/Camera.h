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
	glm::mat4 lookAt, projection;

	static float lastX;
	static float lastY;
	static bool firstMouse;
	static float yaw, pitch;
	static float Zoom;

	float windowsHeight = 0;
	float windowsWidth = 0;
	float deltaTime = 0.0f; // Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	void updateLookat();
	void updateProjection();
	glm::mat4 myLookat();
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
public:

	Camera(GLFWwindow* window,glm::vec3 position, glm::vec3 target, glm::vec3 up, float height, float width);
	void processInput(GLFWwindow *window);
	glm::mat4 getProjection();
	glm::mat4 getViewMatrix();
	
	void updateRotation();
};