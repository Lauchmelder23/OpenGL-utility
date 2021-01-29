#include "object.hpp"

#include <material.hpp>

namespace oglu
{
	Object::Object(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize) :
		VAO(MakeVertexArray(vertices, verticesSize, indices, indicesSize, topology, topologySize)),
		material(new Material)
	{
	}

	Object::Object(const VertexArray& vao) :
		VAO(vao), material(new Material)
	{
	}

	Object::Object(const Object& other) :
		VAO(other.VAO), material(new Material)
	{
	}

	Object::~Object()
	{
	}

	void Object::Render()
	{
		VAO->BindAndDraw();
	}

	void Object::CopyMaterial(const Material& other)
	{
		memcpy(material.get(), &other, sizeof(Material));
	}
}
