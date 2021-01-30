#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include <core.hpp>
#include <glm/glm.hpp>

#include <texture.hpp>
#include <shader.hpp>
#include <vertexArray.hpp>

namespace oglu
{
	struct OGLU_API Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 UV;
	};

	class OGLU_API Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, 
			 const std::vector<GLuint>& indices, 
			 const std::vector<Texture>& textures);
		void Render(Shader& shader);

	private:
		void CreateMesh();

	public:
		std::vector<Vertex>	vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

	private:
		VertexArray VAO;
	};
}

#endif