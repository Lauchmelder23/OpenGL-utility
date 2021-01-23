#include "transformable.hpp"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace oglu
{
	oglu::Transformable::Transformable() :
		transformation(glm::mat4(1.0f))
	{
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
	}

	Transformable::Transformable(const Transformable& other) :
		transformation(other.transformation)
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
		glm::decompose(transformation, scale, orientation, this->translation, skew, perspective);
		this->translation = translation - this->translation;
		transformation = glm::translate(transformation, this->translation);
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
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
		orientation = glm::quat(glm::radians(rotation)) * (-orientation);
		transformation = glm::rotate(transformation, glm::angle(orientation), glm::axis(orientation));
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
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
		orientation = glm::angleAxis(glm::radians(angle), axis) * (-orientation);
		transformation = glm::rotate(transformation, glm::angle(orientation), glm::axis(orientation));
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
		glm::decompose(transformation, this->scale, orientation, translation, skew, perspective);
		this->scale = scale / this->scale;
		if (this->scale.x == INFINITY) this->scale.x = scale.x;
		if (this->scale.y == INFINITY) this->scale.y = scale.y;
		if (this->scale.z == INFINITY) this->scale.z = scale.z;
		transformation = glm::scale(transformation, this->scale);
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
		transformation = glm::translate(transformation, translation);
		glm::decompose(transformation, scale, orientation, this->translation, skew, perspective);
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
		glm::quat rot = glm::quat(glm::radians(rotation));
		transformation = glm::rotate(transformation, glm::angle(rot), glm::axis(rot));
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
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
		transformation = glm::rotate(transformation, glm::radians(angle), axis);
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
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
		transformation = glm::scale(transformation, scale);
		glm::decompose(transformation, this->scale, orientation, translation, skew, perspective);
	}

	const glm::mat4& Transformable::GetMatrix()
	{
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
