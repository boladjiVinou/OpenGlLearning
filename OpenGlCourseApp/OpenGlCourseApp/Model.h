#pragma once
#include <assimp/include/assimp/Importer.hpp>
#include <assimp/include/assimp/scene.h>
#include <assimp/include/assimp/postprocess.h>
#include <assimp/include/assimp/material.h>
#include "Mesh.h";

using namespace std;
class Model
{
public:
	Model(string path)
	{
		loadModel(path);
	}
	void Draw(Shader &shader);
private:
	// model data
	vector<Mesh> meshes;
	string directory;
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Mesh::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};