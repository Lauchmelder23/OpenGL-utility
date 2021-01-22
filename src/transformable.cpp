#include "transformable.hpp"

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace oglu
{
	oglu::Transformable::Transformable() :
		translation(new float[16]), rotation(new float[16]), scaling(new float[16]), calculateMatrix(false)
	{
		glm::mat4 identity(1.0f);
		memcpy(
			translation,
			glm::value_ptr(identity),
			16 * sizeof(float)
		);
		memcpy(
			rotation,
			glm::value_ptr(identity),
			16 * sizeof(float)
		);
		memcpy(
			scaling,
			glm::value_ptr(identity),
			16 * sizeof(float)
		);
	}

	Transformable::Transformable(const Transformable& other) :
		translation(new float[16]), rotation(new float[16]), scaling(new float[16]), calculateMatrix(true)
	{
		memcpy(
			this->translation,
			other.translation,
			16 * sizeof(float)
		);

		memcpy(
			this->rotation,
			other.rotation,
			16 * sizeof(float)
		);

		memcpy(
			this->scaling,
			other.scaling,
			16 * sizeof(float)
		);
	}

	Transformable::~Transformable()
	{
		delete[] scaling;
		delete[] rotation;
		delete[] translation;
	}

	void Transformable::SetPosition(float x, float y, float z)
	{
		memcpy(
			this->translation,
			glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::SetPosition(const float* translation)
	{
		memcpy(
			this->translation,
			glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::make_vec3(translation))),
			16 * sizeof(float)
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
		memcpy(
			this->scaling,
			glm::value_ptr(glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, scaleZ))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::SetScale(const float* scale)
	{
		memcpy(
			this->scaling,
			glm::value_ptr(glm::scale(glm::mat4(1.0f), glm::make_vec3(scale))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::Move(float x, float y, float z)
	{
		memcpy(
			this->translation,
			glm::value_ptr(glm::translate(glm::make_mat4(this->translation), glm::vec3(x, y, z))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::Move(const float* translation)
	{
		memcpy(
			this->translation,
			glm::value_ptr(glm::translate(glm::make_mat4(this->translation), glm::make_vec3(translation))),
			16 * sizeof(float)
		);
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
		memcpy(
			this->scaling,
			glm::value_ptr(glm::scale(glm::make_mat4(this->scaling), glm::vec3(scaleX, scaleY, scaleZ))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Transformable::Scale(const float* scale)
	{
		memcpy(
			this->scaling,
			glm::value_ptr(glm::translate(glm::make_mat4(this->scaling), glm::make_vec3(scale))),
			16 * sizeof(float)
		);
		calculateMatrix = true;
	}

	const float* Transformable::GetMatrix()
	{
		static glm::mat4 transformation(1.0f);

		if (calculateMatrix)
		{
			transformation = glm::make_mat4(translation) * glm::make_mat4(rotation) * glm::make_mat4(scaling);
			calculateMatrix = false;
		}

		return glm::value_ptr(transformation);
	}
}
