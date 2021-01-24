/*****************************************************************//**
 * \file   camera.hpp
 * \brief  A camera object
 * 
 * \author Lauchmelder
 * \date   January 2021
 *********************************************************************/
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <core.hpp>
#include <glm/glm.hpp>

namespace oglu
{
	class Transformable;

	/**
	 * @brief A class that simulates a camera in 3D space.
	 */
	class OGLU_API Camera
	{
	public:
		/**
		 * @brief Create a default camera.
		 * 
		 * Default settings:
		 * Position: (0, 0, 0)
		 * Looking at: Negative Z
		 * FOV: 45.0f
		 * AspectRatio: 1.0f
		 * zNear: 0.1f
		 * zFar: 100.0f
		 */
		Camera();

		/**
		 * @brief Create a new camera.
		 *
		 * @param[in] fov FOV of the camera (in degrees)
		 * @param[in] aspectRatio of the camera
		 * @param[in] zNear Near clipping plane
		 * @param[in] zFar Far clipping plane
		 */
		Camera(float fov, float aspectRatio, float zNear, float zFar);

		/**
		 * Copy another camera.
		 * 
		 * @param[in] other Camera to copy from
		 */
		Camera(const Camera& other);

		/**
		 * @brief Set the cameras position.
		 * 
		 * @param[in] x New x position
		 * @param[in] y New y position
		 * @param[in] z New z position
		 */
		void SetPosition(float x, float y, float z);

		/**
		 * @brief Set the cameras position.
		 *
		 * @param[in] position The new position
		 */
		void SetPosition(const float* position);

		/**
		 * @brief Set the cameras position.
		 *
		 * @param[in] position The new position
		 */
		void SetPosition(const glm::vec3& position);

		/**
		 * @brief Offset the cameras position
		 *
		 * @param[in] x x offset
		 * @param[in] y y offset
		 * @param[in] z z offset
		 */
		void Move(float x, float y, float z);

		/**
		 * @brief Offset the cameras position
		 *
		 * @param[in] offset Offset
		 */
		void Move(const float* offset);

		/**
		 * @brief Offset the cameras position
		 *
		 * @param[in] offset Offset
		 */
		void Move(const glm::vec3& offset);

		/**
		 * @brief Have the camera face a target.
		 * 
		 * Right now the camera cannot roll. @p worldUp is always positive Y
		 * 
		 * @param[in] x x position of the target
		 * @param[in] y y position of the target
		 * @param[in] z z position of the target
		 */
		void LookAt(float x, float y, float z);

		/**
		 * @brief Have the camera face a target.
		 *
		 * Right now the camera cannot roll. @p worldUp is always positive Y
		 *
		 * @param[in] target Coordinates of the target
		 */
		void LookAt(const float* target);

		/**
		 * @brief Have the camera face a target.
		 *
		 * Right now the camera cannot roll. @p worldUp is always positive Y
		 *
		 * @param[in] target Coordinates of the target
		 */
		void LookAt(const glm::vec3& target);

		/**
		 * @brief Have the camera face a target.
		 *
		 * Right now the camera cannot roll. @p worldUp is always positive Y
		 *
		 * @param[in] target A target Transformable
		 */
		void LookAt(const Transformable& target);

		/**
		 * @brief Pan the camera.
		 * 
		 * Panning is a rotation around the cameras local up axis.
		 * 
		 * @param[in] angle Angle to rotate by
		 */
		void Pan(float angle);

		/**
		 * @brief Tilt the camera.
		 *
		 * Panning is a rotation around the cameras local right axis.
		 *
		 * @param[in] angle Angle to rotate by
		 */
		void Tilt(float angle);

		/**
		 * @brief Roll the camera (doesn't work).
		 *
		 * Panning is a rotation around the cameras local front axis.
		 *
		 * @param[in] angle Angle to rotate by
		 */
		void Roll(float angle);

		/**
		 * @brief Get the view matrix.
		 * 
		 * @returns A 4x4 view matrix
		 */
		const glm::mat4& GetMatrix();

		/**
		 * @brief Get the projection matrix.
		 *
		 * @returns A 4x4 projection matrix
		 */
		const glm::mat4& GetProjection();

	private:
		glm::mat4 projection;		///< The projection matrix
		glm::mat4 transformation;	///< The view matrix
		glm::vec3 position;			///< The cameras position
		glm::vec3 front;			///< The cameras front vector
		glm::vec3 right;			///< The cameras right vector
		glm::vec3 up;				///< The cameras up vector

		float fov;					///< FOV of the camera
		float aspectRatio;			///< Aspect ratio of the camera
		float zNear;				///< Near clipping plane
		float zFar;					///< Far clipping plane
	};
}

#endif