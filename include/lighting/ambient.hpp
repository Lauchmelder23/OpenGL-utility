/*****************************************************************//**
 * @file   ambient.hpp
 * @brief  Anything related to ambient/environmental lighting
 * 
 * @author Lauchmelder
 * @date   January 2021
 *********************************************************************/
#ifndef AMBIENT_HPP
#define AMBIENT_HPP

#include <core.hpp>
#include <color.hpp>

namespace oglu
{
	/**
	 * @brief A class holding information needed for ambient lighting.
	 */
	class OGLU_API AmbientLight
	{
	public:
		/**
		 * @brief Create default ambient light.
		 * 
		 * By default, this creates a white light at full intensity
		 */
		AmbientLight();

		/**
		 * @brief Create a custom ambient light.
		 * 
		 * @param r Red component
		 * @param r Green component
		 * @param r Blue component
		 * @param intensity Intensity of the lighting
		 */
		AmbientLight(GLfloat r, GLfloat g, GLfloat b, GLfloat intensity);

		/**
		 * @brief Create a custom ambient light.
		 *
		 * @param color Color of the lighting
		 * @param intensity Intensity of the lighting
		 */
		AmbientLight(const Color& color, GLfloat intensity);

		/**
		 * @brief Copy another ambient light.
		 * 
		 * @param other The light to copy from
		 */
		AmbientLight(const AmbientLight& other);

		GLfloat intensity;	///< Intensity of the ambient light
		Color color;		///< Color of the ambient light
	};
}

#endif