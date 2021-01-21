#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <core.hpp>
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

	class OGLU_API AbstractObject
	{
	public:
		AbstractObject(const AbstractObject& other);
		~AbstractObject();

		friend std::shared_ptr<AbstractObject> OGLU_API MakeObject(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize);

		GLuint GetVAO() { return VAO; }
		void Bind();
		void Unbind();

		void Draw();
		void BindAndDraw();

	private:
		AbstractObject(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize);

		inline void RegisterVertexAttribPointer(GLuint index, const VertexAttribute& topology);

		GLuint VAO;
		GLsizei count;
	};

	typedef std::shared_ptr<AbstractObject> Object;
}

#endif
