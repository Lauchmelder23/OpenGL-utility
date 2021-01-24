#include "camera.hpp"

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <transformable.hpp>

namespace oglu
{
	Camera::Camera() :
		fov(45.0f), aspectRatio(1.0f), zNear(0.1f), zFar(100.0f), position(glm::vec3(0.0f)), transformation(glm::mat4(1.0f))
	{
		projection = glm::perspective(fov, aspectRatio, zNear, zFar);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		LookAt(glm::vec3(0.0f, 0.0f, -1.0f));
	}

	Camera::Camera(float fov, float aspectRatio, float zNear, float zFar) :
		fov(fov), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar), position(glm::vec3(0.0f)), transformation(glm::mat4(1.0f))
	{
		projection = glm::perspective(fov, aspectRatio, zNear, zFar);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		LookAt(glm::vec3(0.0f, 0.0f, -1.0f));
	}

	Camera::Camera(const Camera& other) :
		fov(other.fov), aspectRatio(other.aspectRatio),
		zNear(other.zNear), zFar(other.zFar),
		projection(other.projection), transformation(other.transformation),
		front(other.front), up(other.up), right(other.right),
		position(other.position)
	{
	}

	void Camera::SetPosition(float x, float y, float z)
	{
		this->position = glm::vec3(x, y, z);
		LookAt(this->position + front);
	}

	void Camera::SetPosition(const float* position)
	{
		this->position = glm::make_vec3(position);
		LookAt(this->position + front);
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		this->position = position;
		LookAt(this->position + front);
	}

	void Camera::Move(float x, float y, float z)
	{
		this->position += glm::vec3(x, y, z);
		LookAt(this->position + front);
	}

	void Camera::Move(const float* position)
	{
		this->position += glm::make_vec3(position);
		LookAt(this->position + front);
	}

	void Camera::Move(const glm::vec3& position)
	{
		this->position += position;
		LookAt(this->position + front);
	}

	void Camera::LookAt(float x, float y, float z)
	{
		LookAt(glm::vec3(x, y, z));
	}

	void Camera::LookAt(const float* target)
	{
		LookAt(glm::make_vec3(target));
	}

	void Camera::LookAt(const glm::vec3& target)
	{
		front = glm::normalize(target - position);
		transformation = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
		right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
		up = glm::normalize(glm::cross(right, front));
	}

	void Camera::LookAt(const Transformable& target)
	{
		LookAt(target.GetPosition());
	}

	void Camera::Pan(float angle)
	{
		front = glm::rotate(glm::angleAxis(glm::radians(angle), up), front);
		transformation = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
		right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	void Camera::Tilt(float angle)
	{
		front = glm::rotate(glm::angleAxis(glm::radians(angle), right), front);
		transformation = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
		up = glm::normalize(glm::cross(right, front));
	}

	void Camera::Roll(float angle)
	{
		up = glm::rotate(glm::angleAxis(glm::radians(angle), front), front);
		transformation = glm::lookAt(position, position + front, up);
		right = glm::normalize(glm::cross(front, up));
	}

	const glm::mat4& Camera::GetMatrix()
	{
		return transformation;
	}

	const glm::mat4& Camera::GetProjection()
	{
		return projection;
	}
}
