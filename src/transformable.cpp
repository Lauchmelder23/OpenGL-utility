#include "transformable.hpp"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace oglu
{
	oglu::Transformable::Transformable() :
		transformation(glm::mat4(1.0f)), recalculateMatrix(false)
	{
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
	}

	Transformable::Transformable(const Transformable& other) :
		transformation(other.transformation), recalculateMatrix(false)
	{
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
	}

	Transformable::~Transformable()
	{
	}

	void Transformable::SetPosition(float x, float y, float z)
	{
		SetPosition(glm::vec3(x, y, z));
	}

	void Transformable::SetPosition(const float* translation)
	{
		SetPosition(glm::make_vec3(translation));
	}

	void Transformable::SetPosition(const glm::vec3& position)
	{
		translation = position;
		recalculateMatrix = true;
	}

	void Transformable::SetRotation(float rotX, float rotY, float rotZ)
	{
		SetRotation(glm::vec3(rotX, rotY, rotZ));
	}

	void Transformable::SetRotation(const float* rotation)
	{
		SetRotation(glm::make_vec3(rotation));
	}

	void Transformable::SetRotation(const glm::vec3& rotation)
	{
		orientation = glm::quat(glm::radians(rotation));
		recalculateMatrix = true;
	}

	void Transformable::SetRotation(float angle, float xAxis, float yAxis, float zAxis)
	{
		SetRotation(angle, glm::vec3(xAxis, yAxis, zAxis));
	}

	void Transformable::SetRotation(float angle, const float* axis)
	{
		SetRotation(angle, glm::make_vec3(axis));
	}

	void Transformable::SetRotation(float angle, const glm::vec3& axis)
	{
		orientation = glm::angleAxis(glm::radians(angle), axis);
		recalculateMatrix = true;
	}

	void Transformable::SetScale(float scaleX, float scaleY, float scaleZ)
	{
		SetScale(glm::vec3(scaleX, scaleY, scaleZ));
	}

	void Transformable::SetScale(const float* scale)
	{
		SetScale(glm::make_vec3(scale));
	}

	void Transformable::SetScale(const glm::vec3& scale)
	{
		this->scale = scale;
		recalculateMatrix = true;
	}

	void Transformable::Move(float x, float y, float z)
	{
		Move(glm::vec3(x, y, z));
	}

	void Transformable::Move(const float* translation)
	{
		Move(glm::make_vec3(translation));
	}

	void Transformable::Move(const glm::vec3& translation)
	{
		this->translation += translation;
		recalculateMatrix = true;
	}

	void Transformable::Rotate(float rotX, float rotY, float rotZ)
	{
		Rotate(glm::vec3(rotX, rotY, rotZ));
	}

	void Transformable::Rotate(const float* rotation)
	{
		Rotate(glm::make_vec3(rotation));
	}

	void Transformable::Rotate(const glm::vec3& rotation)
	{
		orientation *= glm::quat(glm::radians(rotation));
		recalculateMatrix = true;
	}

	void Transformable::Rotate(float angle, float xAxis, float yAxis, float zAxis)
	{
		Rotate(angle, glm::vec3(xAxis, yAxis, zAxis));
	}

	void Transformable::Rotate(float angle, const float* axis)
	{
		Rotate(angle, glm::make_vec3(axis));
	}

	void Transformable::Rotate(float angle, const glm::vec3& axis)
	{
		orientation *= glm::angleAxis(glm::radians(angle), axis);
		recalculateMatrix = true;
	}

	void Transformable::Scale(float scaleX, float scaleY, float scaleZ)
	{
		Scale(glm::vec3(scaleX, scaleY, scaleZ));
	}

	void Transformable::Scale(const float* scale)
	{
		Scale(glm::make_vec3(scale));
	}

	void Transformable::Scale(const glm::vec3& scale)
	{
		this->scale += scale;
		recalculateMatrix = true;
	}

	const glm::mat4& Transformable::GetMatrix()
	{
		if (recalculateMatrix)
		{
			transformation = glm::mat4(1.0f);
			transformation = glm::translate(transformation, translation);
			transformation *= glm::toMat4(orientation);
			transformation = glm::scale(transformation, scale);

			recalculateMatrix = false;
		}
		return transformation;
	}

	const glm::vec3& Transformable::GetPosition() const
	{
		return translation;
	}

	const glm::quat& Transformable::GetRotation() const
	{
		return orientation;
	}

	const glm::vec3& Transformable::GetScaling() const
	{
		return scale;
	}
}
