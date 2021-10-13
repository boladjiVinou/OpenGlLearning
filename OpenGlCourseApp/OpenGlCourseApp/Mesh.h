#pragma once
#include <vector>
#include "Shader.h";
#include <string>;
#include <glm/glm.hpp>;
#include <glm/glm.hpp>;
using namespace std;
class Mesh 
{
public:
	struct Texture {
		unsigned int id;
		std::string type;
		string path;
	};

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
	// mesh data
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader &shader);
private:
	// render data
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};