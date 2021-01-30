#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

#include <core.hpp>
#include <shader.hpp>
#include <object.hpp>
#include <model/mesh.hpp>

#include <assimp/scene.h>

namespace oglu
{
	class OGLU_API Model : public Transformable
	{
	public:
		Model(const std::string& path);
		void Render(Shader& shader);

	private:
		std::vector<Texture> loaded;
		std::vector<Mesh> meshes;
		std::string directory;

		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
	};
}

#endif