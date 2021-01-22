#include "object.hpp"

namespace oglu
{
	Object::Object(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize) :
		VAO(MakeVertexArray(vertices, verticesSize, indices, indicesSize, topology, topologySize))
	{
	}

	Object::Object(const Object& other) :
		VAO(other.VAO)
	{
	}

	Object::~Object()
	{
	}

	void Object::Render()
	{
		VAO->BindAndDraw();
	}
}
