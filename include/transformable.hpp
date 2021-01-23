/*****************************************************************//**
 * \file   transformable.hpp
 * \brief  Contains utility for anything that has a geometry
 * 
 * \author Lauchmelder
 * \date   January 2021
 *********************************************************************/

#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include <core.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace oglu
{
	/**
	 * @brief Defines position, rotation and scale.
	 * 
	 * This class wraps a 4x4 transformation matrix and provides useful
	 * helper functions to perform translations, rotations and scalings.
	 */
	class OGLU_API Transformable
	{
	public:
		/**
		 * @brief Create new identity transformation.
		 * 
		 * An identity transformation is a matrix with all 1's on the diagonal.
		 * When applied to a vector it leaves it unchanged.
		 */
		Transformable();

		/**
		 * @brief Copies another transformation.
		 * 
		 * The transformation matrix of @p other is copied.
		 */
		Transformable(const Transformable& other);
		~Transformable();

		/**
		 * @brief Sets the position.
		 * 
		 * This sets an absolute position, means that it resets any previous
		 * translations.
		 * 
		 * @param[in] x New x position
		 * @param[in] y New y position
		 * @param[in] z New z position
		 */
		virtual void SetPosition(float x, float y, float z);

		/**
		 * @brief Sets the position.
		 *
		 * This sets an absolute position, means that it resets any previous
		 * translations.
		 *
		 * @param[in] position An array of floats containing three scalars
		 */
		virtual void SetPosition(const float* position);

		/**
		 * @brief Sets the position.
		 *
		 * This sets an absolute position, means that it resets any previous
		 * translations.
		 *
		 * @param[in] position A 3D position vector
		 */
		virtual void SetPosition(const glm::vec3& position);

		/**
		 * @brief Sets the rotation.
		 *
		 * This sets an absolute rotation, means that it resets any previous
		 * rotations.
		 *
		 * @param[in] rotX New rotation around x axis
		 * @param[in] rotY New rotation around y axis
		 * @param[in] rotZ New rotation around z axis
		 */
		virtual void SetRotation(float rotX, float rotY, float rotZ);

		/**
		 * @brief Sets the rotation.
		 *
		 * This sets an absolute rotation, means that it resets any previous
		 * rotations.
		 *
		 * @param[in] rotation An array of floats containing three scalars
		 */
		virtual void SetRotation(const float* rotation);

		/**
		 * @brief Sets the rotation.
		 *
		 * This sets an absolute rotation, means that it resets any previous
		 * rotations.
		 *
		 * @param[in] rotation A glm::vec3 containing Euler angles
		 */
		virtual void SetRotation(const glm::vec3& rotation);

		/**
		 * @brief Sets the rotation.
		 *
		 * This sets an absolute rotation, means that it resets any previous
		 * rotations.
		 *
		 * @param[in] angle The angle to rotate by
		 * @param[in] xAxis The x component of the rotation axis
		 * @param[in] yAxis The y component of the rotation axis
		 * @param[in] zAxis The z component of the rotation axis
		 */
		virtual void SetRotation(float angle, float xAxis, float yAxis, float zAxis);

		/**
		 * @brief Sets the rotation.
		 *
		 * This sets an absolute rotation, means that it resets any previous
		 * rotations.
		 *
		 * @param[in] angle The angle to rotate by
		 * @param[in] axis An array of floats containing the three rotation axis components
		 */
		virtual void SetRotation(float angle, const float* axis);

		/**
		 * @brief Sets the rotation.
		 *
		 * This sets an absolute rotation, means that it resets any previous
		 * rotations.
		 *
		 * @param[in] angle The angle to rotate by
		 * @param[in] axis The axis to rotate around
		 */
		virtual void SetRotation(float angle, const glm::vec3& axis);

		/**
		 * @brief Sets the scaling.
		 *
		 * This sets an absolute scaling, means that it resets any previous
		 * scaling.
		 *
		 * @param[in] scaleX The scaling in x direction
		 * @param[in] scaleY The scaling in y direction
		 * @param[in] scaleZ The scaling in z direction
		 */
		virtual void SetScale(float scaleX, float scaleY, float scaleZ);

		/**
		 * @brief Sets the scaling.
		 *
		 * This sets an absolute scaling, means that it resets any previous
		 * scaling.
		 *
		 * @param[in] scale An array of floats containing three scalars
		 */
		virtual void SetScale(const float* scale);

		/**
		 * @brief Sets the scaling.
		 *
		 * This sets an absolute scaling, means that it resets any previous
		 * scaling.
		 *
		 * @param[in] scale A 3D scaling vector
		 */
		virtual void SetScale(const glm::vec3& scale);

		/**
		 * @brief Performs a translation.
		 *
		 * This function applies a translation to the object, it operates
		 * operates on the current position.
		 *
		 * @param[in] x Offset along the x axis
		 * @param[in] y Offset along the y axis
		 * @param[in] z Offset along the z axis
		 */
		virtual void Move(float x, float y, float z);

		/**
		 * @brief Performs a translation.
		 *
		 * This function applies a translation to the object, it operates
		 * operates on the current position.
		 *
		 * @param[in] position An array of floats containing the offset values
		 */
		virtual void Move(const float* translation);

		/**
		 * @brief Performs a translation.
		 *
		 * This function applies a translation to the object, it operates
		 * operates on the current position.
		 *
		 * @param[in] position A 3D displacement vector
		 */
		virtual void Move(const glm::vec3& translation);

		/**
		 * @brief Performs a rotation.
		 *
		 * This function applies a rotation to the object, it operates
		 * operates on the current rotation.
		 *
		 * @param[in] rotX Rotation around the x axis
		 * @param[in] rotY Rotation around the y axis
		 * @param[in] rotZ Rotation around the z axis
		 */
		virtual void Rotate(float rotX, float rotY, float rotZ);

		/**
		 * @brief Performs a rotation.
		 *
		 * This function applies a rotation to the object, it operates
		 * operates on the current rotation.
		 *
		 * @param[in] rotation An array of floats containing the rotation values
		 */
		virtual void Rotate(const float* rotation);

		/**
		 * @brief Performs a rotation.
		 *
		 * This function applies a rotation to the object, it operates
		 * operates on the current rotation.
		 *
		 * @param[in] rotation An 3D vector containing Euler angles
		 */
		virtual void Rotate(const glm::vec3& rotation);

		/**
		 * @brief Performs a rotation.
		 *
		 * This function applies a rotation to the object, it operates
		 * operates on the current rotation.
		 *
		 * @param[in] angle The angle to rotate by
		 * @param[in] xAxis x component of the rotation axis
		 * @param[in] yAxis y component of the rotation axis
		 * @param[in] zAxis z component of the rotation axis
		 */
		virtual void Rotate(float angle, float xAxis, float yAxis, float zAxis);

		/**
		 * @brief Performs a rotation.
		 *
		 * This function applies a rotation to the object, it operates
		 * operates on the current rotation.
		 *
		 * @param[in] angle The angle to rotate by
		 * @param[in] axis An array of floats containing the components of the rotation axis
		 */
		virtual void Rotate(float angle, const float* axis);

		/**
		 * @brief Performs a rotation.
		 *
		 * This function applies a rotation to the object, it operates
		 * operates on the current rotation.
		 *
		 * @param[in] angle The angle to rotate by
		 * @param[in] axis The axis to rotate around
		 */
		virtual void Rotate(float angle, const glm::vec3& axis);

		/**
		 * @brief Performs scaling.
		 *
		 * This function applies scaling to the object, it operates
		 * operates on the current scaling.
		 *
		 * @param[in] scaleX Scaling in x direction
		 * @param[in] scaleX Scaling in y direction
		 * @param[in] scaleX Scaling in z direction
		 */
		virtual void Scale(float scaleX, float scaleY, float scaleZ);

		/**
		 * @brief Performs scaling.
		 *
		 * This function applies scaling to the object, it operates
		 * operates on the current scaling.
		 *
		 * @param[in] scale An array of floats containing three scaling values
		 */
		virtual void Scale(const float* scale);

		/**
		 * @brief Performs scaling.
		 *
		 * This function applies scaling to the object, it operates
		 * operates on the current scaling.
		 *
		 * @param[in] scale A 3D scaling vector
		 */
		virtual void Scale(const glm::vec3& scale);

		/**
		 * @brief Returns a transformation matrix.
		 *
		 * @return An array of 16 floats representing the transformation matrix
		 */
		const float* GetMatrix();

		/**
		 * @brief Get position as a 3D vector.
		 * 
		 * @returns A pointer to an array of floats
		 */
		const float* GetPosition() const;

		/**
		 * @brief Get rotation as a matrix.
		 *
		 * @returns A pointer to a 4x4 matrix
		 */
		const float* GetRotation() const;

		/**
		 * @brief Get scaling as a 3D vector.
		 *
		 * @returns A pointer to an array of floats
		 */
		const float* GetScaling() const;

	protected:
		// TODO: Separate translation, rotation and scaling matrices.
		// Combine them only when the user wants the transformation matrix
		glm::mat4 transformation;

		glm::vec3 scale;
		glm::quat orientation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
	};
}

#endif