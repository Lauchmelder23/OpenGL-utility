#include "lighting/point.hpp"

#include <transformable.hpp>

namespace oglu
{
	PointLight::PointLight() :
		position(new glm::vec3(0.0f)), diffusionColor(oglu::Color::White), specularColor(oglu::Color::White)
	{
	}

	PointLight::PointLight(const glm::vec3& position, const Color& diffusionColor, const Color& specularColor) :
		position(new glm::vec3(0.0f)), diffusionColor(diffusionColor), specularColor(specularColor)
	{
		memcpy(this->position, &position, sizeof(glm::vec3));
	}

	PointLight::PointLight(const PointLight& other) :
		position(new glm::vec3(0.0f)), diffusionColor(other.diffusionColor), specularColor(other.specularColor)
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
