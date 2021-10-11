#include <vector>
#include "Vertex.cpp";
#include "Shader.h";
#include "Texture.cpp";
using namespace std;
class Mesh 
{
public:
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