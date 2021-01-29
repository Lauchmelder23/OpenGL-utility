#include "lighting/spotlight.hpp"

namespace oglu
{
	SpotLight::SpotLight() :
		PointLight(), direction(glm::vec3(0.0f, -1.0f, 0.0f)), angle(18.5f), outerAngle(25.0f)
	{
	}

	SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, float angle, const Color& diffusionColor, const Color& specularColor) :
		PointLight(position, diffusionColor, specularColor), direction(glm::vec3(0.0f, -1.0f, 0.0f)), angle(18.5f), outerAngle(25.0f)
	{
	}

	SpotLight::SpotLight(const SpotLight& other) :
		direction(glm::vec3(0.0f, -1.0f, 0.0f)), angle(18.5f), outerAngle(25.0f)
	{
		diffusionColor = other.diffusionColor;
		specularColor = other.specularColor;
		constant = other.constant;
		linear = other.linear;
		quadratic = other.quadratic;
		isLinked = false;

		position = new glm::vec3(0.0f);
		memcpy(this->position, other.position, sizeof(glm::vec3));
	}
}
