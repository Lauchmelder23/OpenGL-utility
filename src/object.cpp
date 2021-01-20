#include "object.hpp"

namespace oglu
{
	Object::Object() :
		VAO(0)
	{
	}

	Object::Object(const GLfloat* vertices, size_t verticesSize, 
					const GLuint* indices, size_t indicesSize, 
					const VertexAttribute* topology, size_t topologySize) :
		VAO(0)
	{
		topologySize /= sizeof(VertexAttribute);

		GLuint VBO;
		glGenBuffers(1, &VBO);

		GLuint EBO;
		glGenBuffers(1, &EBO);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

		for (int i = 0; i < topologySize; i++)
		{
			RegisterVertexAttribPointer(i, topology[i]);
		}

		glBindVertexArray(0);

		count = indicesSize / sizeof(GLuint);
	}

	void Object::Bind()
	{
		glBindVertexArray(VAO);
	}

	void Object::Unbind()
	{
		
	}

	void Object::Draw()
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (GLvoid*)0);
	}

	void Object::BindAndDraw()
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (GLvoid*)0);
		glBindVertexArray(0);
	}

	void Object::RegisterVertexAttribPointer(GLuint index, const VertexAttribute& topology)
	{
		glVertexAttribPointer(topology.index, topology.size, topology.type, topology.normalized, topology.stride, topology.pointer);
		glEnableVertexAttribArray(index);
	}
}