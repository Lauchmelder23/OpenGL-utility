/*****************************************************************//**
 * \file   camera.hpp
 * \brief  Contains anything relevant to cameras
 * 
 * \author Lauchmelder
 * \date   January 2021
 *********************************************************************/
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <core.hpp>
#include <transformable.hpp>

namespace oglu
{
	/**
	 * @brief A camera object in 3D space.
	 * 
	 * This class unites a world- and projection matrix.
	 */
	class OGLU_API Camera : public Transformable
	{
	public:
		/**
		 * @brief Create a default camera.
		 * 
		 * Sits at the origin, looks in negative z-direction.
		 * FOV: 45.0°
		 * Aspect ratio: Matches the viewport
		 * zNear: 0.1f
		 * zFar: 100.0f
		 */
		Camera();

		/**
		 * @brief Copy another camera.
		 *
		 * Every property of @p other is copied.
		 * 
		 * @param[in] other The camera to copy from
		 */
		Camera(const Camera& other);

		/**
		 * @brief Create a new camera.
		 * 
		 * Sits at the origin, looks in negative z-direction.
		 * The other properties are set from the parameters
		 * 
		 * @param[in] fov The FOV (field of view) of the camera
		 * @param[in] aspectRatio The aspect ratio of the camera. (Setting this to 0.f will use your viewport's aspect ratio)
		 * @param[in] zNear Near z clipping plane
		 * @param[in] zNear Far z clipping plane
		 */
		Camera(float fov, float aspectRatio, float zNear, float zFar);

		~Camera();

		/**
		 * @brief Have camera face at a certain position.
		 * 
		 * This will adjust the camera's rotation in order to put the
		 * specified coordinate at the center of the screen.
		 * 
		 * @param[in] x Target x coordinate
		 * @param[in] y Target y coordinate
		 * @param[in] z Target z coordinate
		 */
		void LookAt(GLfloat x, GLfloat y, GLfloat z);

		/**
		 * @brief Have camera face at a certain position.
		 *
		 * This will adjust the camera's rotation in order to put the
		 * specified coordinate at the center of the screen.
		 *
		 * @param[in] target 3D vector with the target position
		 */
		void LookAt(const GLfloat* target);

		/**
		 * @brief Have camera face at a certain position.
		 *
		 * This will adjust the camera's rotation in order to put the
		 * specified coordinate at the center of the screen.
		 *
		 * @param[in] target An object to target
		 */
		void LookAt(const Transformable& target);

		/**
		 * @brief Gets the projection matrix of the camera.
		 * 
		 * @returns a 4x4 projection matrix.
		 */
		const float* GetProjectionMatrix();

	private:
		float aspectRatio;	///< Aspect ration of the camera
		float fov;			///< FOV of the camera
		float zNear;		///< Near z clipping plane
		float zFar;			///< Far z clipping plane

		float* projection;
	};
}

#endif 