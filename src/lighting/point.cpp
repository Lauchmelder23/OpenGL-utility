#include "lighting/point.hpp"

#include <transformable.hpp>

namespace oglu
{
	PointLight::PointLight() :
		position(new glm::vec3(0.0f)), diffusionColor(oglu::Color::White), specularColor(oglu::Color::White),
		constant(1.0f), linear(0.09f), quadratic(0.032f), isLinked(false)
	{
	}

	PointLight::PointLight(const glm::vec3& position, const Color& diffusionColor, const Color& specularColor) :
		position(new glm::vec3(0.0f)), diffusionColor(diffusionColor), specularColor(specularColor),
		constant(1.0f), linear(0.09f), quadratic(0.032f), isLinked(false)
	{
		memcpy(this->position, &position, sizeof(glm::vec3));
	}

	PointLight::PointLight(const PointLight& other) :
		position(new glm::vec3(0.0f)), diffusionColor(other.diffusionColor), specularColor(other.specularColor),
		constant(1.0f), linear(0.09f), quadratic(0.032f), isLinked(false)
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
		isLinked = true;
	}

	void PointLight::UnlinkPositionFromTransformable()
	{
		if (isLinked)
			position = new glm::vec3(*position);

		isLinked = false;
	}

	float* PointLight::GetPositionPointer()
	{
		return &((*position)[0]);
	}
}
