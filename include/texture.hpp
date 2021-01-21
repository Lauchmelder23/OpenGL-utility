/*****************************************************************//**
 * \file   texture.hpp
 * \brief  Contains functions and objects relevant to textures
 * 
 * \author Robert
 * \date   January 2021
 *********************************************************************/

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <core.hpp>

namespace oglu
{
	/**
	 * @relates AbstractTexture
	 * @brief Set active texture unit
	 * 
	 * @param[in] index Index of the texture unit (Note: This index is actually an offset to @p GL_TEXTURE0)
	 */
	void OGLU_API ActiveTexture(GLubyte index);

	/**
	 * @brief An object representing an OpenGL Texture.
	 *
	 * This class contains the OpenGL Texture and supplies the user
	 * with functions to operate on this texture.
	 *
	 * This class cannot be instantiated, this should be done via MakeTexture(const char* filename).
	 */
	class OGLU_API AbstractTexture
	{
	public:
		/**
		 * @brief Constructs a new texture.
		 *
		 * Use this function to create new textures.
		 *
		 * @param[in] vertexShaderFile Filepath to the image file
		 *
		 * @return A shared pointer to the texture.
		 */
		friend std::shared_ptr<AbstractTexture> OGLU_API MakeTexture(const char* filename);

		/**
		 * @brief Copy constructor.
		 *
		 * Copying a texture is generally possible. Since the user is given a shared pointer the
		 * texture is only deleted once every instance has been deconstructed.
		 *
		 * @param[in] other Texture to copy from
		 */
		AbstractTexture(const AbstractTexture& other);
		~AbstractTexture();

		/**
		 * @brief Bind this texture.
		 */
		void Bind();

		/**
		 * @brief Unbind this texture.
		 */
		void Unbind();

	private:
		/**
		 * @brief Construct a texture.
		 *
		 * To avoid accidental deletion of textures while they're still in use,
		 * this constructor has been made private. To create a texture use
		 * MakeTexture(const char* filename).
		 *
		 * @param[in] vertexShaderFile Filepath to the image file
		 */
		AbstractTexture(const char* filename);

	private:
		int width;		///< Width of the loaded image
		int height;		///< Height of the loaded image
		int nrChannels;	///< Channels of the loaded image
		GLuint texture;	///< OpenGL handle to the texture
	};

	typedef std::shared_ptr<AbstractTexture> Texture;
}

#endif