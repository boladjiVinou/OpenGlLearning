#pragma once
#include <assimp/include/Importer.hpp>
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h>
#include <assimp/include/material.h>
#include "Mesh.h";

using namespace std;
class Model
{
public:
	Model(string path)
	{
		this->path = path;
	}
	void loadModel();
	void Draw(Shader &shader);
private:
	// model data
	vector<Mesh> meshes;
	string directory;
	string path;
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Mesh::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};