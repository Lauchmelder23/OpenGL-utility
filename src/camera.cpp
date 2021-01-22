#include "camera.hpp"

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
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
		glm::mat4 newTransform = glm::lookAt(glm::make_vec3(position), glm::vec3(x, y, z), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec3 scale;
		glm::vec3 pos;
		glm::quat rot;
		glm::vec3 skew;
		glm::vec4 pers;
		glm::decompose(newTransform, scale, rot, pos, skew, pers);

		memcpy(
			position,
			glm::value_ptr(pos),
			3 * sizeof(float)
		);

		memcpy(
			rotation,
			glm::value_ptr(glm::toMat4(rot)),
			16 * sizeof(float)
		);

		memcpy(
			scaling,
			glm::value_ptr(scale),
			3 * sizeof(float)
		);
		calculateMatrix = true;
	}

	void Camera::LookAt(const GLfloat* target)
	{
		LookAt(target[0], target[1], target[2]);
	}

	void Camera::LookAt(const Transformable& target)
	{
		LookAt(target.GetPosition());
	}

	const float* Camera::GetProjectionMatrix()
	{
		return projection;
	}
}
