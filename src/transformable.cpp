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
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
		translation = glm::vec3(x, y, z) - translation;
		transformation = glm::translate(transformation, translation);
	}

	void Transformable::SetPosition(const float* translation)
	{
		glm::decompose(transformation, scale, orientation, this->translation, skew, perspective);
		this->translation = glm::make_vec3(translation) - this->translation;
		transformation = glm::translate(transformation, this->translation);
	}

	void Transformable::SetRotation(float rotX, float rotY, float rotZ)
	{
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
		orientation = glm::quat(glm::vec3(rotX, rotY, rotZ)) - orientation;
		transformation = glm::rotate(transformation, orientation.w, glm::vec3(orientation.x, orientation.y, orientation.z));
	}

	void Transformable::SetRotation(const float* rotation)
	{
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
		orientation = glm::quat(glm::make_vec3(rotation)) - orientation;
		transformation = glm::rotate(transformation, orientation.w, glm::vec3(orientation.x, orientation.y, orientation.z));
	}

	void Transformable::SetRotation(float angle, float xAxis, float yAxis, float zAxis)
	{
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
		orientation = glm::quat(glm::vec4(xAxis, yAxis, zAxis, angle)) - orientation;
		transformation = glm::rotate(transformation, orientation.w, glm::vec3(orientation.x, orientation.y, orientation.z));
	}

	void Transformable::SetRotation(float angle, const float* axis)
	{
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
		orientation = glm::quat(glm::vec4(axis[0], axis[1], axis[2], angle)) - orientation;
		transformation = glm::rotate(transformation, orientation.w, glm::vec3(orientation.x, orientation.y, orientation.z));
	}

	void Transformable::SetScale(float scaleX, float scaleY, float scaleZ)
	{
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
		scale = glm::vec3(scaleX, scaleY, scaleZ) - scale;
		transformation = glm::scale(transformation, scale);
	}

	void Transformable::SetScale(const float* scale)
	{
		glm::decompose(transformation, this->scale, orientation, translation, skew, perspective);
		this->scale = glm::make_vec3(scale) - this->scale;
		transformation = glm::scale(transformation, this->scale);
	}

	void Transformable::Move(float x, float y, float z)
	{
		transformation = glm::translate(transformation, glm::vec3(x, y, z));
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
	}

	void Transformable::Move(const float* translation)
	{
		transformation = glm::translate(transformation, glm::make_vec3(translation));
		glm::decompose(transformation, scale, orientation, this->translation, skew, perspective);
	}

	void Transformable::Rotate(float rotX, float rotY, float rotZ)
	{
		transformation = glm::rotate(transformation, glm::radians(1.0f), glm::vec3(rotX, rotY, rotZ));
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
	}

	void Transformable::Rotate(const float* rotation)
	{
		transformation = glm::rotate(transformation, 1.0f, glm::make_vec3(rotation));
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
	}

	void Transformable::Rotate(float angle, float xAxis, float yAxis, float zAxis)
	{
		transformation = glm::rotate(transformation, angle, glm::vec3(xAxis, yAxis, zAxis));
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
	}

	void Transformable::Rotate(float angle, const float* axis)
	{
		transformation = glm::rotate(transformation, angle, glm::make_vec3(axis));
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
	}

	void Transformable::Scale(float scaleX, float scaleY, float scaleZ)
	{
		transformation = glm::scale(transformation, glm::vec3(scaleX, scaleY, scaleZ));
		glm::decompose(transformation, scale, orientation, translation, skew, perspective);
	}

	void Transformable::Scale(const float* scale)
	{
		transformation = glm::scale(transformation, glm::make_vec3(scale));
		glm::decompose(transformation, this->scale, orientation, translation, skew, perspective);
	}

	const float* Transformable::GetMatrix()
	{
		return glm::value_ptr(transformation);
	}

	const float* Transformable::GetPosition() const
	{
		return glm::value_ptr(translation);
	}

	const float* Transformable::GetRotation() const
	{
		return glm::value_ptr(orientation);
	}

	const float* Transformable::GetScaling() const
	{
		return glm::value_ptr(scale);
	}
}
