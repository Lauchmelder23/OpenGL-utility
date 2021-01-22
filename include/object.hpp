/*****************************************************************//**
 * \file   object.hpp
 * \brief  Representation of objects in 3D space
 * 
 * \author Lauchmelder
 * \date   January 2021
 *********************************************************************/
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <core.hpp>
#include <transformable.hpp>
#include <vertexArray.hpp>

namespace oglu
{
	/**
	 * @brief An object in 3D space.
	 * 
	 * This class combines a 3D model with a Transformable. This class
	 * is designed to be imagined as a literal object in 3D space.
	 */
	class OGLU_API Object : public Transformable
	{
	public:
		/**
		 * @brief Create a new object.
		 * 
		 * No transformations are applied to this object.
		 * 
		 * @param[in] vertices		Array of vertex data
		 * @param[in] verticesSize	Size of vertex array
		 * @param[in] indices		Array of index data
		 * @param[in] indicesSize	Size of index array
		 * @param[in] topology		Array of VertexAttribute
		 * @param[in] topologySize	Size of topology array
		 */
		Object(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize);
		
		/**
		 * @brief Create a new object.
		 * 
		 * No transformations are applied to this object.
		 * 
		 * @param[in] vao The VAO to use for rendering
		 */
		Object(const VertexArray& vao);

		/**
		 * @brief Copy another object.
		 * 
		 * After copying these two objects will share the same VAO. However
		 * the transformation matrix is copied so that the two objects can be
		 * spatially independent.
		 * 
		 * @param[in] other The object to copy from
		 */
		Object(const Object& other);
		~Object();

		/**
		 * @brief Render the object
		 */
		void Render();

	private:
		VertexArray VAO;	///< The VAO used for rendering
	};
}

#endif