#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <core.hpp>
#include <transformable.hpp>
#include <vertexArray.hpp>

namespace oglu
{
	class OGLU_API Object : public Transformable
	{
	public:
		Object(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize);
		Object(const Object& other);
		~Object();

		void Render();

	private:
		VertexArray VAO;
	};
}

#endif