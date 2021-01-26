#include "lighting/point.hpp"

#include <transformable.hpp>

namespace oglu
{
	PointLight::PointLight() :
		position(new glm::vec3(0.0f)), color(oglu::Color::White)
	{
	}

	PointLight::PointLight(const glm::vec3& position, const Color& color) :
		position(new glm::vec3(0.0f)), color(color)
	{
		memcpy(this->position, &position, sizeof(glm::vec3));
	}

	PointLight::PointLight(const PointLight& other) :
		position(new glm::vec3(0.0f)), color(other.color)
	{
		memcpy(this->position, position, sizeof(glm::vec3));
	}

	PointLight::~PointLight()
	{
		if(!isLinked)
			delete position;
	}

	void PointLight::LinkPositionToTransformable(Transformable& link)
	{
		if (!isLinked)
			delete position;

		position = &link.translation;
	}

	void PointLight::UnlinkPositionFromTransformable()
	{
		if (isLinked)
			position = new glm::vec3(0.0f);
	}

	float* PointLight::GetPositionPointer()
	{
		return &((*position)[0]);
	}
}
