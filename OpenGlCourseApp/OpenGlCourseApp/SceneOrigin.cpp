#include "SceneOrigin.h"
SceneOrigin::SceneOrigin()
{
	float vertices_color[] =
	{
		0.0f,0.0f,0.0f,			1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,			1.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,			0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,			0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,			0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,			0.0f,0.0f,1.0f,
	};
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_color), vertices_color, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int shaderProgram = glCreateProgram();
	_vertexShader = new Shader(vertexShaderSource, GL_VERTEX_SHADER);
	_fragmentShader = new Shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	_vertexShader->AttachShaderTo(shaderProgram);
	_fragmentShader->AttachShaderTo(shaderProgram);
}
SceneOrigin::~SceneOrigin()
{
	delete _vertexShader;
	_vertexShader = nullptr;
	delete _fragmentShader;
	_fragmentShader = nullptr;
}
void SceneOrigin::displayOrigin(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix)
{
	glBindVertexArray(_vao);
	_vertexShader->useProgram();
	_vertexShader->setMat4(MODEL_MATRIX_NAME, glm::mat4(1.0f));
	_vertexShader->setMat4(VIEW_MATRIX_NAME, viewMatrix);
	_vertexShader->setMat4(PROJECTION_MATRIX_NAME, projectionMatrix);
	glDrawArrays(GL_LINES, 0, 6);
}