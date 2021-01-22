/*****************************************************************//**
 * \file   vertexArray.hpp
 * \brief  Contains functions and objects relevant to VAOs
 * 
 * \author Robert
 * \date   January 2021
 *********************************************************************/

#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <core.hpp>

namespace oglu
{
	/**
	 * @brief Structure to store topology data.
	 */
	struct OGLU_API VertexAttribute {
		/*@{*/
		GLuint index;			///< Index of the vertex attribute
		GLint size;				///< Number of elements in this attribute
		GLenum type;			///< Datatype of the elements
		GLboolean normalized;	///< Normalize fixed-point data
		GLsizei stride;			///< Byte offset between these attributes
		const GLvoid* pointer;	///< Offset of this attribute into the data
		/*@}*/
	};

	/**
	 * @brief An object representing an OpenGL VAO.
	 *
	 * This class contains the OpenGL VAO and supplies the user
	 * with functions to operate on this VAO.
	 *
	 * This class cannot be instantiated, this should be done via MakeVertexArray().
	 */
	class OGLU_API AbstractVertexArray
	{
	public:
		/**
		 * @brief Constructs a new VAO.
		 *
		 * Use this function to create new VAOs.
		 *
		 * @param[in] vertices		Array of vertex data
		 * @param[in] verticesSize	Size of vertex array
		 * @param[in] indices		Array of index data
		 * @param[in] indicesSize	Size of index array
		 * @param[in] topology		Array of VertexAttribute 
		 * @param[in] topologySize	Size of topology array
		 *
		 * @return A shared pointer to the texture.
		 */
		friend std::shared_ptr<AbstractVertexArray> OGLU_API MakeVertexArray(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize);

		/**
		 * @brief Constructs a new VAO.
		 * 
		 * Reads an .obj file and converts it into a VAO
		 * 
		 * @param[in] filepath Path to the .obj file
		 */
		friend std::shared_ptr<AbstractVertexArray> OGLU_API MakeVertexArray(const char* filepath);

		/**
		 * @brief Copy constructor.
		 *
		 * Copying a VAO is generally possible. Since the user is given a shared pointer the
		 * VAO is only deleted once every instance has been deconstructed.
		 *
		 * @param[in] other VAO to copy from
		 */
		AbstractVertexArray(const AbstractVertexArray& other);
		~AbstractVertexArray();

		/**
		 * @brief Bind this VAO.
		 */
		void Bind();

		/**
		 * @brief Unbind this VAO.
		 */
		void Unbind();

		/**
		 * @brief Draw this VAO.
		 * 
		 * This function does not bind the VAO before drawing, be careful when using this. Also see: BindAndDraw()
		 */
		void Draw();

		/**
		 * @brief Draw this VAO.
		 * 
		 * This function binds, draws, then unbinds the VAO. Also see: Draw()
		 */
		void BindAndDraw();

	private:
		/**
		 * @brief Construct a VAO.
		 *
		 * To avoid accidental deletion of VAO while they're still in use,
		 * this constructor has been made private. To create a texture use
		 * MakeVertexArray().
		 *
		 * @param[in] vertices		Array of vertex data
		 * @param[in] verticesSize	Size of vertex array
		 * @param[in] indices		Array of index data
		 * @param[in] indicesSize	Size of index array
		 * @param[in] topology		Array of VertexAttribute 
		 * @param[in] topologySize	Size of topology array
		 */
		AbstractVertexArray(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize);

		/**
		 * @brief Registers and enables a Vertex Attribute Pointer.
		 */
		inline void RegisterVertexAttribPointer(GLuint index, const VertexAttribute& topology);

		// TODO: Create new class for Buffer objects. Then multiple VAOs can use the same buffers
		GLuint VAO;		///< Handle to OpenGL VAO
		GLuint VBO;		///< Handle to OpenGL VBO
		GLuint EBO;		///< Handle to OpenGL EBO
		GLsizei count;	///< Amount of indices
	};

	typedef std::shared_ptr<AbstractVertexArray> VertexArray;
}

#endif
