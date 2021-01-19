#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "core.hpp"
#include <glad/glad.h>

namespace oglu
{
	typedef OGLU_API struct {
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const GLvoid* pointer;
	} VertexAttribute;

	class OGLU_API Object
	{
	public:
		Object();
		Object(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize);

		GLuint GetVAO() { return VAO; }

	private:
		GLuint VAO;
	};
}

#endif
