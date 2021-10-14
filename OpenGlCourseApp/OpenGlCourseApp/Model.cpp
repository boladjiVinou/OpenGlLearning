#include "Model.h";
#include "TextureLoader.h";
#include <algorithm>;

void Model:: Draw(Shader &shader) 
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}

void Model::loadModel() 
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
		!scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node, const aiScene *scene)
{
	// process all the node’s meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Mesh::Vertex> vertices;
	vector<unsigned int> indices;
	vector<Mesh::Texture> textures;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Mesh::Vertex vertex;
		// process vertex positions, normals and texture coordinates
		if (mesh->HasNormals()) 
		{
			vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		}
		if (mesh->HasTextureCoords(0)) 
		{
			vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		vertex.Position = glm::vec3( mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertices.push_back(vertex);
	}
	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Mesh::Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Mesh::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(),
			specularMaps.end());
	}
	return Mesh(vertices, indices, textures);

}
vector<Mesh::Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
	vector<Mesh::Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		TextureLoader TextureLoader;
		string dir = directory + "/" + str.C_Str();
		auto isAlreadyLoaded = [dir](Mesh::Texture pTexture) { return pTexture.path == dir; };
		if (std::find_if(textures.begin(), textures.end(), isAlreadyLoaded) == textures.end()) {
			{
				Mesh::Texture texture;
				texture.id = TextureLoader.loadTexture(&dir[0]);
				texture.type = typeName;
				texture.path = dir;
				textures.push_back(texture);
			}
		}
	}
	return textures;
}