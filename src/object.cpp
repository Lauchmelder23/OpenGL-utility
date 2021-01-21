#include "object.hpp"

namespace oglu
{
	AbstractObject::AbstractObject(const AbstractObject& other) :
		VAO(other.VAO), VBO(other.VBO), EBO(other.EBO), count(other.count)
	{

	}

	AbstractObject::~AbstractObject()
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	Object MakeObject(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize)
	{
		AbstractObject* obj = new AbstractObject(vertices, verticesSize, indices, indicesSize, topology, topologySize);
		return Object(obj);
	}

	AbstractObject::AbstractObject(const GLfloat* vertices, size_t verticesSize, 
					const GLuint* indices, size_t indicesSize, 
					const VertexAttribute* topology, size_t topologySize) :
		VAO(0), VBO(0), EBO(0), count(0)
	{
		topologySize /= sizeof(VertexAttribute);

		glGenBuffers(1, &VBO);
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

	void AbstractObject::Bind()
	{
		glBindVertexArray(VAO);
	}

	void AbstractObject::Unbind()
	{
		glBindVertexArray(0);
	}

	void AbstractObject::Draw()
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (GLvoid*)0);
	}

	void AbstractObject::BindAndDraw()
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (GLvoid*)0);
		glBindVertexArray(0);
	}

	void AbstractObject::RegisterVertexAttribPointer(GLuint index, const VertexAttribute& topology)
	{
		glVertexAttribPointer(topology.index, topology.size, topology.type, topology.normalized, topology.stride, topology.pointer);
		glEnableVertexAttribArray(index);
	}
}