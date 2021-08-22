#include "Camera.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
using namespace std;

void Camera:: updateLookat()
{
	lookAt = myLookat();//glm::lookAt(position, cameraFront, up);
}
void Camera::updateRotation()
{
	glm::vec3 direction = glm::vec3();
	float radYaw = glm::radians(yaw);
	float radPitch = glm::radians(pitch);
	direction.x = cos(radYaw)* cos(radPitch);
	direction.y = sin(radPitch);
	direction.z = sin(radYaw)* cos(radPitch);
	cameraFront = glm::normalize(direction);
	cameraFront.x *= far;
	cameraFront.y *= far;
	cameraFront.z *= far;
}

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float far)
{
	this->position = position;
	this->target = target;
	this->up = up;
	this->far = far;
	lookAt = glm::lookAt(position, target, up);
}
void Camera::processInput(GLFWwindow *window)
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	float cameraSpeed = 2.5f * deltaTime;// adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += cameraSpeed * glm::normalize(cameraFront);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= cameraSpeed * glm::normalize(cameraFront);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
	}
	updateLookat();
}

glm::mat4 Camera::getViewMatrix()
{ 
	return lookAt;
}

void Camera:: mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += xoffset;
	pitch += yoffset;
}

glm::mat4 Camera::myLookat()
{
	glm::mat4 lookAtMat = glm::mat4(1);
	
	glm::vec3 dir = glm::normalize(position - cameraFront);
	glm::vec3 right = glm::normalize(glm::cross(up, dir));
	glm::vec3 tmpUp = glm::cross(dir, right);
	lookAtMat[0][0] = right.x;
	lookAtMat[1][0] = right.y;
	lookAtMat[2][0] = right.z;
	lookAtMat[0][1] = tmpUp.x;
	lookAtMat[1][1] = tmpUp.y;
	lookAtMat[2][1] = tmpUp.z;
	lookAtMat[0][2] = dir.x;
	lookAtMat[1][2] = dir.y;
	lookAtMat[2][2] = dir.z;
	glm::mat4 translateMat = glm::mat4(1);
	translateMat[3][0] = -position.x;
	translateMat[3][1] = -position.y;
	translateMat[3][2] = -position.z;
	lookAtMat = lookAtMat *translateMat;

	return lookAtMat;
}
float Camera::lastX = 400;
float Camera::lastY = 300;
bool Camera::firstMouse = true;
float Camera::yaw = -90;
float Camera::pitch = 0;