#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <core.hpp>

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

	class OGLU_API AbstractVertexArray
	{
	public:
		AbstractVertexArray(const AbstractVertexArray& other);
		~AbstractVertexArray();

		friend std::shared_ptr<AbstractVertexArray> OGLU_API MakeObject(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize);

		GLuint GetVAO() { return VAO; }
		void Bind();
		void Unbind();

		void Draw();
		void BindAndDraw();

	private:
		AbstractVertexArray(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize);

		inline void RegisterVertexAttribPointer(GLuint index, const VertexAttribute& topology);

		GLuint VAO, VBO, EBO;
		GLsizei count;
	};

	typedef std::shared_ptr<AbstractVertexArray> VertexArray;
}

#endif
