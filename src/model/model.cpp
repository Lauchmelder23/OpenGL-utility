#include "model/model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace oglu
{
	Model::Model(const std::string& path)
	{
		LoadModel(path);
	}

	void Model::Render(Shader& shader)
	{
		for (Mesh& mesh : meshes)
			mesh.Render(shader);
	}

	void Model::LoadModel(const std::string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::string errStr = importer.GetErrorString();
			importer.FreeScene();
			throw std::runtime_error(errStr);
		}

		directory = path.substr(0, path.find_last_of('/'));
		ProcessNode(scene->mRootNode, scene);

		importer.FreeScene();
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

			if (mesh->mTextureCoords[0])
				vertex.UV = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			else
				vertex.UV = glm::vec2(0.0f);

			vertices.push_back(vertex);
		}

		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "tex_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "tex_spec");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
	{
		std::vector<Texture> textures;
		
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (GLuint j = 0; j < loaded.size(); j++)
			{
				if (std::strcmp(loaded[j]->filepath.data(), str.C_Str()))
				{
					textures.push_back(loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				Texture texture = MakeTexture((directory + "/" + std::string(str.C_Str())).c_str(), typeName + std::to_string(i));
				loaded.push_back(texture);
				textures.push_back(texture);
			}
		}

		return textures;
	}
}
