#include "transformable.hpp"

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace oglu
{
	oglu::Transformable::Transformable() :
		position(new float[3]{ 0.f }), rotation(new float[16]), scaling(new float[3]{ 1.f, 1.f, 1.f }), transformation(new float[16]), calculateMatrix(false)
	{
		glm::mat4 identity(1.0f);
		memcpy(
			rotation,
			glm::value_ptr(identity),
			16 * sizeof(float)
		);
		memcpy(
			transformation,
			glm::value_ptr(identity),
			16 * sizeof(float)
		);
	}

	Transformable::Transformable(const Transformable& other) :
		position(new float[3]), rotation(new float[16]), scaling(new float[3]), transformation(new float[16]), calculateMatrix(true)
	{
		memcpy(
			this->position,
			other.position,
			3 * sizeof(float)
		);

		memcpy(
			this->rotation,
			other.rotation,
			16 * sizeof(float)
		);

		memcpy(
			this->scaling,
			other.scaling,
			3 * sizeof(float)
		);
	}

	Transformable::~Transformable()
	{
		delete[] scaling;
		delete[] rotation;
		delete[] position;
	}

	void Transformable::SetPosition(float x, float y, float z)
	{
		this->position[0] = x;
		this->position[1] = y;
		this->position[2] = z;
		calculateMatrix = true;
	}

	void Transformable::SetPosition(const float* translation)
	{
		memcpy(
			this->position,
			translation,
			3 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::SetRotation(float rotX, float rotY, float rotZ)
	{
		// TODO: Using rotation matrices is stupid. Eventually this could (should) be done with quaternions
		// For now we'll just risk gimbal locking the model
		memcpy(
			this->rotation,
			glm::value_ptr(
				glm::rotate(
					glm::rotate(
						glm::rotate(
							glm::mat4(1.0f), glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f)
						), glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f)
					), glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f)
				)
			),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::SetRotation(const float* rotation)
	{
		memcpy(
			this->rotation,
			glm::value_ptr(
				glm::rotate(
					glm::rotate(
						glm::rotate(
							glm::mat4(1.0f), glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)
						), glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f)
					), glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f)
				)
			),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::SetRotation(float angle, float xAxis, float yAxis, float zAxis)
	{
		memcpy(
			this->rotation,
			glm::value_ptr(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(xAxis, yAxis, zAxis))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::SetRotation(float angle, const float* axis)
	{
		memcpy(
			this->rotation,
			glm::value_ptr(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::make_vec3(axis))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::SetScale(float scaleX, float scaleY, float scaleZ)
	{
		this->scaling[0] = scaleX;
		this->scaling[1] = scaleY;
		this->scaling[2] = scaleZ;
		calculateMatrix = true;
	}

	void Transformable::SetScale(const float* scale)
	{
		memcpy(
			this->scaling,
			scale,
			3 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::Move(float x, float y, float z)
	{
		this->position[0] += x;
		this->position[1] += y;
		this->position[2] += z;
		calculateMatrix = true;
	}

	void Transformable::Move(const float* translation)
	{
		this->position[0] += translation[0];
		this->position[1] += translation[1];
		this->position[2] += translation[2];
		calculateMatrix = true;
	}

	void Transformable::Rotate(float rotX, float rotY, float rotZ)
	{
		memcpy(
			this->rotation,
			glm::value_ptr(
				glm::rotate(
					glm::rotate(
						glm::rotate(
							glm::make_mat4(this->rotation), glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f)
						), glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f)
					), glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f)
				)
			),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::Rotate(const float* rotation)
	{
		memcpy(
			this->rotation,
			glm::value_ptr(
				glm::rotate(
					glm::rotate(
						glm::rotate(
							glm::make_mat4(this->rotation), glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)
						), glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f)
					), glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f)
				)
			),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::Rotate(float angle, float xAxis, float yAxis, float zAxis)
	{
		memcpy(
			this->rotation,
			glm::value_ptr(glm::rotate(glm::make_mat4(this->rotation), glm::radians(angle), glm::vec3(xAxis, yAxis, zAxis))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::Rotate(float angle, const float* axis)
	{
		memcpy(
			this->rotation,
			glm::value_ptr(glm::rotate(glm::make_mat4(this->rotation), glm::radians(angle), glm::make_vec3(axis))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::Scale(float scaleX, float scaleY, float scaleZ)
	{
		this->scaling[0] += scaleX;
		this->scaling[1] += scaleY;
		this->scaling[2] += scaleZ;
		calculateMatrix = true;
	}

	void Transformable::Scale(const float* scale)
	{
		this->scaling[0] += scale[0];
		this->scaling[1] += scale[1];
		this->scaling[2] += scale[2];
		calculateMatrix = true;
	}

	const float* Transformable::GetMatrix()
	{
		if (calculateMatrix)
		{
			memcpy(
				transformation,
				glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::make_vec3(position)) * glm::make_mat4(rotation) * glm::scale(glm::mat4(1.0f), glm::make_vec3(scaling))),
				16 * sizeof(float)
			);
			calculateMatrix = false;
		}

		return transformation;
	}

	const float* Transformable::GetPosition() const
	{
		return position;
	}

	const float* Transformable::GetRotation() const
	{
		return rotation;
	}

	const float* Transformable::GetScaling() const
	{
		return scaling;
	}
}
