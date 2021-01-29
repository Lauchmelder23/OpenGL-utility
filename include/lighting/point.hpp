/*****************************************************************//**
 * @file   point.hpp
 * @brief  Anything related to point light sources
 *
 * @author Lauchmelder
 * @date   January 2021
 *********************************************************************/
#ifndef POINT_HPP
#define POINT_HPP

#include <core.hpp>
#include <color.hpp>
#include <glm/glm.hpp>

namespace oglu
{
	class Transformable;

	/**
	 * @brief A class containing things related to point lighting.
	 */
	class OGLU_API PointLight
	{
	public:
		/**
		 * @brief Create a default point light.
		 * 
		 * By default the diffusion and specular components are white and
		 * the light is positioned at the world origin
		 */
		PointLight();

		/**
		 * @brief Create a new point light.
		 * 
		 * @param position Position of the light
		 * @param diffusionColor Color of the diffusion component
		 * @param specularColor Color of the specular component
		 */
		PointLight(const glm::vec3& position, const Color& diffusionColor = Color::White, const Color& specularColor = Color::White);
		
		/**
		 * @brief Copy from another point light.
		 * 
		 * @param other The point light to copy from
		 */
		PointLight(const PointLight& other);

		~PointLight();

		/**
		 * @brief Link the lights position to a Transformable.
		 * 
		 * It is possible to link the positions of a Transformable and
		 * a PointLight. This means that these two objects will always
		 * have the same position, until they are unlinked. Deleting a
		 * Transformable before unlinking any linked PointLight causes
		 * undefined behaviour.
		 * 
		 * @param link The Transformable to link to
		 */
		void LinkPositionToTransformable(Transformable& link);

		/**
		 * @brief Unlink a Transformable.
		 * 
		 * This breaks the link between the two objects.
		 */
		void UnlinkPositionFromTransformable();

		/**
		 * Get the lights position.
		 * 
		 * @returns A pointer to the lights position
		 */
		float* GetPositionPointer();

	public:
		// TODO: Does this split make sense? I'll keep it for now
		Color diffusionColor;	///< Diffusion color of the light
		Color specularColor;	///< Specular color of the light


	private:
		glm::vec3* position;	///< Position of the light
		bool isLinked;			///< Wether the position is linked to an object or not
	};
}

#endif