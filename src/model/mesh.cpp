#include "model/mesh.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace oglu
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures) :
		vertices(vertices), indices(indices), textures(textures)
	{
		CreateMesh();
	}

	void Mesh::Render(Shader& shader)
	{
		GLuint diffuseIndex = 1;
		GLuint bumpIndex = 1;
		
		for (GLuint i = 0; i < textures.size(); i++)
		{
			textures[i]->BindAs(i);
		}
		ActiveTexture(0);

		VAO->BindAndDraw();
	}

	void Mesh::CreateMesh()
	{
		VertexAttribute topology[] = {
			{0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0},
			{1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)},
			{2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV)}
		};

		VAO = MakeVertexArray(
			glm::value_ptr(vertices[0].Position), sizeof(Vertex) * vertices.size(),
			&indices[0], sizeof(GLuint) * indices.size(),
			topology, sizeof(topology)
		);
	}
}