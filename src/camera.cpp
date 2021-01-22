#include "camera.hpp"

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace oglu
{
	Camera::Camera() :
		fov(45.0f), aspectRatio(0.0f), zNear(0.1f), zFar(100.0f), projection(new float[16]{ 0.0f })
	{
		memcpy(
			projection,
			glm::value_ptr(glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar)),
			16 * sizeof(float)
		);
	}

	Camera::Camera(const Camera& other) :
		fov(other.fov), aspectRatio(other.aspectRatio), zNear(other.zNear), zFar(other.zFar), projection(new float[16]{ 0.0f })
	{
		memcpy(
			projection,
			other.projection,
			16 * sizeof(float)
		);
	}

	Camera::Camera(float fov, float aspectRatio, float zNear, float zFar) :
		fov(fov), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar), projection(new float[16]{ 0.0f })
	{
		if (aspectRatio == 0.0f)
		{
			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			aspectRatio = (float)viewport[2] / (float)viewport[3];
		}

		memcpy(
			projection,
			glm::value_ptr(glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar)),
			16 * sizeof(float)
		);
	}

	Camera::~Camera()
	{
	}

	void Camera::LookAt(GLfloat x, GLfloat y, GLfloat z)
	{
	}

	void Camera::LookAt(const GLfloat* target)
	{
	}

	void Camera::LookAt(const Object& target)
	{
	}

	const float* Camera::GetProjectionMatrix()
	{
		return projection;
	}
}
